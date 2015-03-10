/*
 * kernel.c
 *
 * Jong-Chan Kim
 */
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "kernel.h"
#include "led.h"

/* global variables */
extern hwc_t ground_component;

uint32_t delayed_output_pending[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

hwc_t components[MAX_COMPONENTS];
int n_components = 0;

uint32_t volatile jiffies = 0;

hwc_t running_component = NULL;
swc_t running_task;

/* for CAN componentizing */
ubyte canMsgValidbit[N_MSG];
ubyte canTdmMap[N_CAN_SLOT];
uword canSlotWalker;

/* for variable timer interrupt (unit:us)*/
ubyte sIsFirstCycle;
uword sHyperPeriod;

typedef struct ScheduleInfo sInfo;
sInfo *sHead, *sTail;
struct ScheduleInfo {
	uword releaseTime;
	uword deadline;
	ubyte isFinished;	/* 0 if false, 1 if true*/
	swc_t runnableTask, idleTask;
	sInfo* next;
};

sInfo *sWalker;
sInfo sInfoPool[N_SINFO_POOL];
ubyte sInfoDirtybit[N_SINFO_POOL];

/* global variables end */

void initSInfoPool(uword hyperPeriodUs)
{
	int i;
	sIsFirstCycle = TRUE;
	sHyperPeriod = hyperPeriodUs; // 10ms
	for(i=0; i < N_SINFO_POOL; i++) {
		memset(&sInfoPool[i], 0, sizeof(sInfo));
		sInfoDirtybit[i] = FALSE;
	}
	sHead = NULL;
	sTail = NULL;
}

sInfo* getSInfoFromPool()
{
	int i;
	for(i=0; i < N_SINFO_POOL; i++) {
		if(sInfoDirtybit[i] == FALSE) {
			sInfoDirtybit[i] = TRUE;
			return &sInfoPool[i];
		}
	}

	return NULL;
}

void freeSInfo(sInfo* target)
{
	int i;
	target->releaseTime		= 0;
	target->deadline		= 0;
	target->isFinished		= FALSE;
	target->runnableTask	= NULL;
	target->idleTask		= NULL;
	target->next			= NULL;

	for(i=0; i < N_SINFO_POOL; i++) {
		if(&sInfoPool[i] == target) {
			sInfoDirtybit[i] = FALSE;
			return;
		}
	}
}

void addScheduleInfo(uword releaseTime, uword deadline, swc_t runnableTask, swc_t idleTask)
{
	ubyte didAdd = FALSE;
	sInfo *prevSInfo, *walker;
	sInfo *newSInfo = getSInfoFromPool();
	if(newSInfo == NULL) return;

	newSInfo->releaseTime = releaseTime;
	newSInfo->deadline = deadline;
	newSInfo->isFinished = FALSE;
	newSInfo->runnableTask = runnableTask;
	newSInfo->idleTask = idleTask;
	if(sHead == NULL) {
		sHead = newSInfo;
		sTail = sHead;
		sHead->next = sTail;
	} else {
		walker = sHead;
		prevSInfo = sTail;
		while(walker != sTail) {
			if(releaseTime < walker->releaseTime) {
				didAdd = TRUE;
				if(prevSInfo->next == sHead)
					sHead = newSInfo;
				newSInfo->next = prevSInfo->next;
				prevSInfo->next = newSInfo;
				break;
			}
			prevSInfo = walker;
			walker = walker->next;
		}
	}

	if(didAdd == FALSE) {
		newSInfo->next = sHead;
		sTail->next = newSInfo;
		sTail = newSInfo;
	}
}

void config_timer(uword us, char sel)
{
	unsigned int additionalU=0; //, mSize;
	//additionalU = us / pow(2,13) / 90;
	additionalU = us / 91;
	//mSize = log(additionalU) / 0.69314718;

	/*
	if(mSize > 31) mSize = 31;
	else */if(additionalU == 0) {
		additionalU = 1;
	}

	switch(sel) {
	case 0:
		STM_CMP0.U = (uint32_t)(STM_CMP0.U + (uint32_t)additionalU);
		//STM_CMP0.U = additionalU;
		/*
		STM_CMCON.B.MSIZE0 = 31;
		STM_CMCON.B.MSTART0 = 13;
		*/
		break;
	case 1:
		STM_CMP1.U = (uint32_t)(STM_CMP1.U + (uint32_t)additionalU);
		STM_CMCON.B.MSIZE1 = 31;
		STM_CMCON.B.MSTART1 = 13;
		break;
	}
}

void init_hardware(void)
{
    printf("Starting Garda Kernel...\n");
    pll_init();
    printf("    PLL initialized\n");
    led_init();
    printf("    LED initialized\n");
    led_off_all();
	can_init();
    printf("    CAN initialized\n");
    initSInfoPool(100000); // 10ms
}

int can_init(void)
{
	CAN_vInit();

	canSlotWalker = 0;
	memset(canMsgValidbit, (int)FALSE, sizeof(ubyte)*N_MSG);
	memset(canTdmMap, (int)NULL, sizeof(ubyte)*N_CAN_SLOT);

	/* Componentized CAN setting */
	can_map(0, 0x00);
	can_map(1, 0x01);
	/*
	can_map(2, 0);
	can_map(3, 1);
	*/
	can_map(10, 0x0b);
	can_map(15, 0x0c);
	can_map(20, 0x0d);

	return 0;
}

void request(int mo_id, ubyte *data)
{
	if ( canMsgValidbit[mo_id] == FALSE ) {
		canMsgValidbit[mo_id] = TRUE;
		CAN_vLoadData((ubyte)mo_id, data);
	}
}

hwc_t get_running_component(void)
{
    return running_component;
}

void set_running_component(hwc_t component)
{
	running_component = component;
}

int create_component(hwc_t component)
{
    component->next_release_time = component->offset;
    component->absolute_deadline = component->offset + component->relative_deadline;
    component->remaining_budget = 0;

    memset(component->runnable_tasks, 0x00, sizeof(component->runnable_tasks));
    memset(component->suspended_tasks, 0x00, sizeof(component->suspended_tasks));
    component->runnable_tasks_bitmap = 0x00000000;

    components[n_components] = component;
    n_components++;

    return 0;
}

int create_task(hwc_t component, swc_t task, task_attr_t attr, void (*func)(void *), uint32_t is_suspended_on_creation)
{
    struct task_attr_s default_attr = TASK_ATTR_DEFAULT;

    uint32_t fcx;
    context_t *cx;

    if (attr == NULL)
        attr = &default_attr;

    fcx = __mfcr(FCX);
    task->lcx = fcx - 1;
    __mtcr(FCX, fcx - 2);

    cx = cx_to_addr(fcx);
    cx->u.psw = 0 << 12 // Protection Register Set PRS=0
            | attr->mode << 10 // I/O Privilege
            | 0 << 9 // Current task uses a user stack IS=0
            | 0 << 8 // Write permission to global registers A0, A1, A8, A9 is disabled
            | 1L << 7 // Call depth counting is enabled CDE=1
            | attr->call_depth_overflow; // Call Depth Overflow
    cx->u.a10 = task->stack + *task->stack; // stack grow down
    cx->u.a11 = 0; // New task has no return address
    cx->u.pcxi = 0; // No previous context;
    cx--;
    cx->l.pcxi = 0L << 24 // Previous CPU Priority Number PCPN=0
            | 1L << 23 // Previous Interrupt Enable PIE=1
            | 1L << 22 // Upper Context Tag.
            | fcx; // Previous Context Pointer is the upper context
    cx->l.pc = func; // init new task start address

//    cx->l.a4 = arg;   // we don't need
//    task->arg = arg;

    uint32_t i = task->priority;

    if (is_suspended_on_creation)
    {
    	// the first release time of the task on the time line
        task->next_release_time = component->offset;
        task->absolute_deadline = component->offset + task->relative_deadline;
        (component->suspended_tasks)[i] = task;
    }
    else	// start IDLE task by marking it is runnable from the task creation.
    {
    	// the first release time of the task on the time line
        task->next_release_time = component->offset;
        task->absolute_deadline = component->offset + task->relative_deadline;
        (component->runnable_tasks)[i] = task;
        __putbit(1, (int*)&(component->runnable_tasks_bitmap), i); // mark current thread ready
    }
    return 0;
}

swc_t get_running_task(void)
{
	return running_task;
}

uint32_t get_jiffies(void)
{
    return jiffies;
}

inline void init_timer_interrupt(void)
{
	/* Schedule module */
	sWalker = sHead;
	STM_CMP0.U = 1;
	STM_CMCON.B.MSIZE0 = 0;
	STM_CMCON.B.MSTART0 = 16;
	STM_ICR.B.CMP0EN = 1;
	STM_ICR.B.CMP0OS = 0;
	STM_SRC0.U = 0x1000 | SCHEDULER_PRIORITY;

    /* CAN componentizing module */
    STM_CMP1.U = 3;
    STM_CMCON.B.MSIZE1 = 1;
    STM_CMCON.B.MSTART1 = 15;
    STM_ICR.B.CMP1EN = 1;
    STM_ICR.B.CMP1OS = 1;
    STM_SRC1.U = 0x1000 | CANCOM_PRIORITY;
}

inline void start_kernel(void)
{
	running_task = ground_component->runnable_tasks[31 - __clz(running_component->runnable_tasks_bitmap)];

   	__dsync();
    __mtcr(PCXI, running_task->lcx);
    __rslcx();
    //__asm(" mov d2,#0"); what is this?
    __asm(" rfe");
}

inline void schedule(void)
{
   	/* RM scheduler */
	/*
   	running_task = (running_component->runnable_tasks)[31 - __clz(running_component->runnable_tasks_bitmap)];
   	*/

	/* Event-driven scheduler */
	if(sIsFirstCycle == TRUE)			  { running_task = sWalker->idleTask; }
	else if(sWalker->isFinished == FALSE) { running_task = sWalker->runnableTask; }
	else								  { running_task = sWalker->idleTask; }

   	__dsync();
    __mtcr(PCXI, running_task->lcx);
    __rslcx();
    //__asm(" mov d2,#0"); what is this?
    __asm(" rfe");
}

static void syscall_trap_handler(void) {
    int tin, priority;

    __asm(" mov %0,d15 \n"
            " svlcx        "
            : "=d"(tin)); // put d15 in C variable tin

    running_task->lcx = __mfcr(PCXI);
    priority = running_task->priority;

    switch (tin) {
    case SYSCALL_SUSPEND:
    	/*
    	(running_component->runnable_tasks)[priority] = NULL;
        (running_component->suspended_tasks)[priority] = running_task;
        __putbit(neza((running_component->runnable_tasks)[priority]), (int*)&(running_component->runnable_tasks_bitmap), priority);
        */

    	sWalker->isFinished = TRUE;
        break;
    case SYSCALL_ABORT:
    	if (running_component->dual_state == DUAL_HIGH)
    	{
			// Suspend current running task
			running_component->runnable_tasks[priority] = NULL;
			running_component->suspended_tasks[priority] = running_task;
			__putbit(neza((running_component->runnable_tasks)[priority]), (int*)&(running_component->runnable_tasks_bitmap), priority);

    		hwc_t trust_component = running_component->link_component;
    		set_running_component(trust_component);
    	}
    	break;
    case SYSCALL_RESUME:
        break;

    default:
        break;
    }

    schedule();
}

//! Trap vector table entry to trap class 6 handler enables interrupts
void __trap_fast(6) syscall_trap(void)
{
	__asm(" mtcr #65068,%0 \n"  /* 65068 = ICR */
            " isync      \n"
            " jg syscall_trap_handler"
            ::"d"(1 << 8 | USER_INTERRUPT_LEVEL),"a"(syscall_trap_handler):"a4", "a5", "d15");//
}

void set_delayed_output(int mo_id, uint32_t timer)
{
	delayed_output_pending[mo_id] = timer;
}

void link(hwc_t high, hwc_t trust)
{
	high->dual_state = DUAL_HIGH;
	high->link_component = trust;

	trust->dual_state = DUAL_TRUST;
	trust->link_component = high;
}

void work_area_start(void)
{
	running_component->is_finished = FALSE;
}

void work_area_end(void)
{
	running_component->is_finished = TRUE;
}

uint32_t check_high_finished(void)
{
	return running_component->link_component->is_finished;
}

void schedule_event_driven_ISR(void)
{
	uword nextInterruptTime;

	running_task->lcx = __mfcr(PCXI);

	if( sIsFirstCycle == FALSE) {
		sWalker = sWalker->next;
	} else {
		sIsFirstCycle = FALSE;
		STM_CMCON.B.MSIZE0 = 31;
		STM_CMCON.B.MSTART0 = 13;
	}

	sWalker->isFinished = FALSE;
	running_task = sWalker->runnableTask;

	if(sWalker == sTail) {
		nextInterruptTime = sHyperPeriod - sWalker->releaseTime + sWalker->next->releaseTime;
	} else {
		nextInterruptTime = sWalker->next->releaseTime - sWalker->releaseTime;
	}
	config_timer(nextInterruptTime, 0);

	//printf("clock diff : %ld", (unsigned long long)(clock() - start));

	__dsync();
	__mtcr(PCXI, running_task->lcx);
	__asm("ji a11");
}

void schedule_EDF_ISR(void)
{
    static uint32_t is_first_time = TRUE;
    int i, j;
//    clock_t start = clock();

    running_task->lcx = __mfcr(PCXI);

    /* schedule next timer interrupt */
	if (jiffies == 0)
	{
		STM_CMP0.U = (uint32_t) (STM_TIM0.U + (uint32_t) TIMER_TICKS);
		STM_CMCON.B.MSIZE0 = 31;
		STM_CMCON.B.MSTART0 = 0;
	}
	else
	{
		STM_CMP0.U = (uint32_t) (STM_CMP0.U + (uint32_t) TIMER_TICKS);
	}

    if (is_first_time)
    {
        jiffies = 0;
        is_first_time = FALSE;
    }
    else
    {
        jiffies++;
        running_component->remaining_budget--;
    }
    /* NOTE: some variables such as next_release_time, deadline are based on absolute time */

    /* release tasks at the start of each period */
    for (i = 0; i < n_components - 1; i++) {
        for (j = 0; j < MAX_PRIORITY; j++) {

        	if (components[i]->runnable_tasks[j] != NULL && components[i]->runnable_tasks[j]->absolute_deadline == jiffies)
        	{
        		// Deadline miss of high performance component
        		if (components[i]->dual_state == DUAL_HIGH)
        		{
        			// Switch to trust (turn on the trust component)
        		}
        		else if (components[i]->dual_state == DUAL_TRUST)
        		{
        			// ERROR: SYSTEM FAILURE
        			// Nothing to do (at this time)
        		}
        	}

        	if (components[i]->runnable_tasks[j] != NULL && components[i]->runnable_tasks[j]->next_release_time == jiffies) {
        		/* end of period while running */
        		/* set next release time and skip this instance */
        		(components[i]->runnable_tasks)[j]->next_release_time += (components[i]->runnable_tasks)[j]->period;
        	}
        	else if (components[i]->suspended_tasks[j] != NULL && components[i]->suspended_tasks[j]->next_release_time == jiffies) {
            	/* normal operation */
            	/* end of period while suspended */
        		/* release this task */
        		components[i]->runnable_tasks[j] = components[i]->suspended_tasks[j];
        		components[i]->suspended_tasks[j] = NULL;
        		__putbit(1, (int*)&(components[i]->runnable_tasks_bitmap), j);

        		/* set next release time */
        		components[i]->runnable_tasks[j]->next_release_time += (components[i]->runnable_tasks)[j]->period;
                /* set next deadline */
        		components[i]->runnable_tasks[j]->absolute_deadline += (components[i]->runnable_tasks)[j]->period;
        		/* get the release time */
        		components[i]->runnable_tasks[j]->release_timestamp = clock();
        	}
        }
    }

    /* replenish new server execution budget at the start of each server period */
    for (i = 0; i < n_components - 1; i++) {
    	if (components[i]->next_release_time == jiffies) {
    		/* set next release time */
    		components[i]->next_release_time += components[i]->period;
    		/* set next deadline */
    		components[i]->absolute_deadline += components[i]->period;
    		/* replenish the component budget */
    		components[i]->remaining_budget = components[i]->budget;
    	}
    }

    /* parent scheduler */
    int earliest_deadline = INT_MAX;
    hwc_t next_component = ground_component;
    for (i = 0; i < n_components - 1; i++) {
        if (components[i]->remaining_budget > 0) {
            if (components[i]->absolute_deadline < earliest_deadline) {
                earliest_deadline = components[i]->absolute_deadline;
                next_component = components[i];
            }
        }
    }
    running_component = next_component;

   	/* RM scheduler */
   	running_task = (running_component->runnable_tasks)[31 - __clz(running_component->runnable_tasks_bitmap)];

   	//printf("clock diff : %ld", (unsigned long long)(clock() - start));

    __dsync();
    __mtcr(PCXI, running_task->lcx);
    __asm("ji a11");
}

void cancom_timer_interrupt_handler(void)
{
    ubyte msgid;

    running_task->lcx = __mfcr(PCXI);

    /* handle delayed outputs */
    for (ubyte k = 0; k < 20; k++) {
    	if (delayed_output_pending[k] == jiffies) {
    		CAN_vTransmit(k);
    		delayed_output_pending[k] = 0;
    	}
    }

    /* CAN message sending as componentized architecture */
	msgid = can(canSlotWalker);
	if ( canMsgValidbit[msgid] == TRUE ) {
		CAN_vTransmit(msgid);
		canMsgValidbit[msgid] = FALSE;
	}
	if ( ++canSlotWalker == N_CAN_SLOT ) {
		canSlotWalker = 0;
	}

	__dsync();
	__mtcr(PCXI, running_task->lcx);
	__asm("ji a11");
}

/* timer interrupt handler */
void __interrupt(SCHEDULER_PRIORITY) schedule_timer_interrupt(void) {
	__asm(" st.t  0xf0000240:0,#1 \n"  // enable interrupts again. Same as STM_ISRR.B.CMP0IRR = 1
          " svlcx        \n"
          " jla schedule_event_driven_ISR \n" // schedule_EDF_ISR, schedule_event_driven_ISR
		  " rslcx");
}

void __interrupt(CANCOM_PRIORITY) cancom_timer_interrupt(void) {
	__asm(" st.t  0xf0000240:0,#1 \n"  // enable interrupts again. Same as STM_ISRR.B.CMP1IRR = 1
          " svlcx        \n"
          " jla cancom_timer_interrupt_handler \n"
		  " rslcx");
}
