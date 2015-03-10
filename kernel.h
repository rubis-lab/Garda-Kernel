#ifndef __KERNEL_H__
#define __KERNEL_H__
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <sfr/regtc1797.sfr>

#include "constants.h"
#include "configs.h"
#include "intrinsic.h"
#include "assert.h"
#include "led.h"
#include "MAIN.h"
#include "CAN.h"

#define can_map(idx, msgid) canTdmMap[idx] = msgid;
#define can(idx)			canTdmMap[idx]

typedef struct swc_s {
    uint32_t task_state;
    uint32_t absolute_deadline;		// absolute deadline
    uint32_t relative_deadline;
    uint32_t next_release_time;		// time instant when the next task job releases
    uint32_t lcx;
    uint32_t priority;
    uint32_t period;
    clock_t release_timestamp;				// release time stamp by clock()
    uint32_t *arg;
    uint32_t stack[1];
} *swc_t;

typedef struct hwc_s {
    uint32_t dual_state;			// DualMode: high performance or trust worthy or nothing
    uint32_t is_finished;			// DualMode: indicates high performance component finishes it tasks
    struct hwc_s* link_component;	// DualMode: high/trust linked component
	uint32_t period;
    uint32_t budget;
    uint32_t relative_deadline;
    uint32_t offset;
    uint32_t next_release_time;		// time instant when the next component job releases
    uint32_t remaining_budget;
    uint32_t absolute_deadline;		// absolute deadline
    swc_t runnable_tasks[MAX_PRIORITY];
    swc_t suspended_tasks[MAX_PRIORITY];
    uint32_t runnable_tasks_bitmap;
} *hwc_t;

typedef struct task_attr_s {
    enum user_e mode;//!< thread mode must be 0 user_e
    uint32_t call_depth_overflow;
    uint32_t stacksize;
} *task_attr_t;

#define DECLARE_SWC(_name,_priority,_period,_deadline,_stacksize,_is_active) static struct { \
    uint32_t task_state; \
    uint32_t absolute_deadline; \
    uint32_t relative_deadline; \
    uint32_t next_release_time; \
    uint32_t lcx; \
    uint32_t priority; \
    uint32_t period; \
    clock_t release; \
    uint32_t *arg; \
    uint32_t stack[_stacksize]; \
    } _##_name = {_is_active, _deadline,_deadline,0,0,_priority,_period,0,NULL,{_stacksize+1}};\
    \
    swc_t _name = (swc_t)&_##_name;

#define DECLARE_HWC(_name, _period, _budget, _deadline, _offset) static struct { \
    uint32_t dual_state; \
    uint32_t is_finished; \
    hwc_t link_component; \
    uint32_t period; \
    uint32_t budget; \
    uint32_t relative_deadline; \
    uint32_t offset; \
    uint32_t next_release_time; \
    uint32_t remaining_budget; \
    uint32_t absolute_deadline; \
	swc_t runnable_tasks[MAX_PRIORITY]; \
    swc_t suspended_tasks[MAX_PRIORITY]; \
    uint32_t runnable_tasks_bitmap; \
    } _##_name = {DUAL_NONE, FALSE, NULL, _period, _budget, _deadline, _offset}; \
    \
    hwc_t _name = (hwc_t)&_##_name;

int can_init(void);
int pll_init(void);
void init_hardware(void);

hwc_t get_running_component(void);
swc_t get_running_task(void);

void set_running_component(hwc_t component);

uint32_t get_jiffies(void);

int create_component(hwc_t component);
int create_task(hwc_t component, swc_t task, task_attr_t attr, void (*func)(void *), uint32_t arg);

void init_timer_interrupt(void);

void start_kernel(void);
void schedule(void);

/* for CAN Msg and send func */
void set_delayed_output(int mo_id, uint32_t timer);
void request(int mo_id, ubyte *data);

/* for DualMode */
void link(hwc_t high, hwc_t trust);
void abort();

void work_area_start(void);
void work_area_end(void);
uint32_t check_high_finished(void);

/* for variable schedule interrupt */
void addScheduleInfo(uword releaseTime, uword deadline, swc_t runnableTask, swc_t idleTask);

__syscallfunc(SYSCALL_ABORT) int syscall_abort(void);
__syscallfunc(SYSCALL_SUSPEND) int syscall_suspend(void);
__syscallfunc(SYSCALL_RESUME) int syscall_resume(void);

#endif /* __KERNEL_H__ */
