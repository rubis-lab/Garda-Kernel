#include "user_main.h"
#if 1

enum user_input_name{ACCELERATION, BRAKE, STEER, LEAD_DISTANCE};
enum car_output_name{SPEED, RPM, YAW_RATE, LATERAL_DISTANCE};

static void func_high(void *arg);
static void func_high2(void *arg);
static void func_trust(void *arg);
static void func_idle(void* arg);
static void func_idle2(void* arg);

#pragma align 8

#define LED_VISIBLE
#ifdef LED_VISIBLE
DECLARE_HWC(hwc_high_1, 50, 10, 20, 0)
DECLARE_HWC(hwc_high_2, 50, 10, 20, 20)
DECLARE_HWC(hwc_trust_1, 50, 20, 30, 20)
DECLARE_HWC(ground_component, 0, 0, 0, 0)    // ground component, or idle component

/*
DECLARE_HWC(dummy1_component, 100, 5, 10, 0)
DECLARE_HWC(dummy2_component, 100, 5, 10, 10)
DECLARE_HWC(dummy3_component, 100, 5, 10, 20)
DECLARE_HWC(dummy4_component, 100, 5, 10, 30)
DECLARE_HWC(dummy5_component, 100, 5, 10, 40)
DECLARE_HWC(dummy6_component, 100, 5, 10, 50)
*/

DECLARE_SWC(swc_high_1, 1, 50, 10, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(swc_high_idle_1, 0, 0, 0, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(swc_high_2, 1, 50, 10, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(swc_high_idle_2, 0, 0, 0, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(swc_trust_1, 1, 50, 20, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(swc_trust_idle_1, 0, 0, 0, DEFAULT_STACK_SIZE, TASK_ACTIVE)
#else
DECLARE_HWC(hwc_high_1, 50, 2, 10, 0);
DECLARE_HWC(hwc_trust_1, 50, 1, 5, 10);
DECLARE_HWC(ground_component, 0, 0, 0, 0);    // ground component, or idle component

DECLARE_SWC(swc_high_1, 1, 50, 10, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(swc_high_idle_1, 0, 0, 0, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(swc_trust_1, 1, 50, 5, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(swc_trust_idle_1, 0, 0, 0, DEFAULT_STACK_SIZE, TASK_ACTIVE)
#endif

DECLARE_SWC(gnd_task, 0, 0, 0, DEFAULT_STACK_SIZE, TASK_ACTIVE)

/*
DECLARE_SWC(dummy1_task, 1, 100, 10, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(dummy2_task, 2, 100, 20, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(dummy3_task, 3, 100, 30, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(dummy4_task, 4, 100, 40, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(dummy5_task, 5, 100, 50, DEFAULT_STACK_SIZE, TASK_ACTIVE)
DECLARE_SWC(dummy6_task, 6, 100, 60, DEFAULT_STACK_SIZE, TASK_ACTIVE)
*/

#pragma align restore

void callback(uint32_t swc_id, uint32_t flag)
{
    switch (swc_id) {
        case 1:
            swc_high_1->task_state = flag;
            break;
        case 2:
            swc_trust_1->task_state = flag;
            break;
        default:
        	break;
    }
}


void user_main(void)
{
    printf("Starting HW/SW Components...\n");
    printf("Starting User Tasks...\n");

    create_component(hwc_high_1);
    create_task(hwc_high_1, swc_high_1, NULL, func_high, FALSE);
    create_task(hwc_high_1, swc_high_idle_1, NULL, func_idle, FALSE);

    create_component(hwc_trust_1);
    create_task(hwc_trust_1, swc_trust_1, NULL, func_trust, TRUE);
    create_task(hwc_trust_1, swc_trust_idle_1, NULL, func_idle, FALSE);

    link(hwc_high_1, hwc_trust_1);

    create_component(hwc_high_2);
    create_task(hwc_high_2, swc_high_2, NULL, func_high2, FALSE);
    create_task(hwc_high_2, swc_high_idle_2, NULL, func_idle2, FALSE);

    /*
    create_component(dummy1_component);
    create_task(dummy1_component, dummy1_task, NULL, func_idle, FALSE);
    create_component(dummy2_component);
    create_task(dummy2_component, dummy2_task, NULL, func_idle, FALSE);
    create_component(dummy3_component);
    create_task(dummy3_component, dummy3_task, NULL, func_idle, FALSE);
    create_component(dummy4_component);
    create_task(dummy4_component, dummy4_task, NULL, func_idle, FALSE);
    create_component(dummy5_component);
    create_task(dummy5_component, dummy5_task, NULL, func_idle, FALSE);
    create_component(dummy6_component);
    create_task(dummy6_component, dummy6_task, NULL, func_idle, FALSE);
    */

    create_component(ground_component);
    create_task(ground_component, gnd_task, NULL, func_idle, FALSE);

    /* Event-driven scheduler test unit */
    addScheduleInfo(1000, 2000, swc_high_1, swc_high_idle_1);	// 0 ~ 1 ms in hyper period
    addScheduleInfo(20000, 25000, swc_high_2, swc_high_idle_2);	// 1 ~ 2 ms in hyper period
    /* test unit end */

    /* Enable timer interrupt */
    printf("Starting The Timer Interrupt...\n");
    init_timer_interrupt();

    set_running_component(hwc_high_1);

    /* only the idle swc is running after calling schedule() and before the 1st timer interrupt */
    printf("Starting The Scheduler...\n");

    schedule();
}

static uint32_t enable_loop(void)
{
	if (get_running_task()->task_state == TASK_INF_LOOP)
		return TRUE;

	return FALSE;
}
static uint32_t check_the_result(void)
{
	if (get_running_task()->task_state != TASK_INVALID_RESULT)
		return TRUE;

	return FALSE;
}

static void func_high(void *arg)
{
    float car_output[14 + 10];
	float user_input[5 + 10];
	CAN_SWObj CC_sensing_1, CC_sensing_2;
    CAN_SWObj LKAS_sensing;
	ubyte send_buf[16]={0,};

	while (1) {
		work_area_start();

#ifdef LED_VISIBLE
		led_on(0);
		delay_ms_f(3);
#endif

		CAN_vGetMsgObj(0x7FF-0x7FD, &CC_sensing_1);		// speed 2
		CAN_vReleaseObj(0x7FF-0x7FD);
		CAN_vGetMsgObj(0x7FF-0x7FB, &CC_sensing_2);		// rpm, yaw rate 4
		CAN_vReleaseObj(0x7FF-0x7FB);
		CAN_vGetMsgObj(0x7FF-0x7F5, &LKAS_sensing);		// lateral distance 10
		CAN_vReleaseObj(0x7FF-0x7F5);

		car_output[SPEED] = *((float *)&CC_sensing_1.ubData[0]);
		car_output[RPM] = *((float *)&CC_sensing_2.ubData[0]);
		car_output[YAW_RATE] = *((float *)&CC_sensing_2.ubData[4]);
		car_output[LATERAL_DISTANCE] = *((float *)&LKAS_sensing.ubData[0]);

		user_input[LEAD_DISTANCE] = 15.0;
		user_input[STEER] = (-4.0 - car_output[LATERAL_DISTANCE]) * 18;
		user_input[ACCELERATION] = ((60.0 - car_output[SPEED]) / 60.0);
		user_input[BRAKE] = 0.0;

		if ( swc_high_1->task_state == TASK_ACTIVE ) {
			memcpy(&send_buf[0], &user_input[ACCELERATION], 4);
			memcpy(&send_buf[4], &user_input[BRAKE], 4);
			CAN_vLoadData(0x7FF-0x7FF, (ubyte *)send_buf);
			memcpy(&send_buf[0], &user_input[STEER], 4);
			memcpy(&send_buf[4], &user_input[LEAD_DISTANCE], 4);
			CAN_vLoadData(0x7FF-0x7FE, (ubyte *)send_buf);

/*
		int cursor = 0;
		int isNormal = 0;
		CAN_vLoadData(12, (ubyte *)send_buf);
		while(1) {
			if ( ++cursor % 5000000 == 0 ) {
				if ( isNormal == 0 ) isNormal = 1;
				else isNormal = 0;
			}
			if ( isNormal == 0 )
				CAN_vTransmit(12);
		}
*/
		/*
		while(1) {
			request(12, (ubyte *)send_buf);
		}
		*/

#ifdef LED_VISIBLE
		led_off(0);
#endif

		// Dummy loop for the test
		/*
		while (enable_loop())
		{
		*/
#ifdef LED_VISIBLE
		/*
			led_on(3);
			delay_ms_f(3);
			led_off(3);
			delay_ms_f(3);
			*/
#endif
		//}


			set_delayed_output(0x7FF-0x7FF, get_running_component()->next_release_time - get_running_component()->period + get_running_component()->relative_deadline);
			set_delayed_output(0x7FF-0x7FE, get_running_component()->next_release_time - get_running_component()->period + get_running_component()->relative_deadline);
			work_area_end();
		}


		// Check the result is valid
		/*
		if (check_the_result())
		{
			set_delayed_output(0x7FF-0x7FF, get_running_component()->next_release_time - get_running_component()->period + get_running_component()->relative_deadline);
			set_delayed_output(0x7FF-0x7FE, get_running_component()->next_release_time - get_running_component()->period + get_running_component()->relative_deadline);
			work_area_end();
		}
		*/

		syscall_suspend();
   }
}

static void func_trust(void *arg)
{
    float car_output[14 + 10];
	float user_input[5 + 10];
	CAN_SWObj CC_sensing_1, CC_sensing_2;
    CAN_SWObj LKAS_sensing;
	ubyte send_buf[16];

    while (1) {
    	if (check_high_finished() == FALSE)
    	{

#ifdef LED_VISIBLE
    		led_off(1);
    		/*
			led_on(1);
			delay_ms_f(3);
			*/
#endif

			CAN_vGetMsgObj(0x7FF-0x7FD, &CC_sensing_1);		// speed
			CAN_vReleaseObj(0x7FF-0x7FD);
			CAN_vGetMsgObj(0x7FF-0x7FB, &CC_sensing_2);		// rpm, yaw rate
			CAN_vReleaseObj(0x7FF-0x7FB);
			CAN_vGetMsgObj(0x7FF-0x7F5, &LKAS_sensing);		// lateral distance
			CAN_vReleaseObj(0x7FF-0x7F5);

			car_output[SPEED] = *((float *)&CC_sensing_1.ubData[0]);
			car_output[RPM] = *((float *)&CC_sensing_2.ubData[0]);
			car_output[YAW_RATE] = *((float *)&CC_sensing_2.ubData[4]);
			car_output[LATERAL_DISTANCE] = *((float *)&LKAS_sensing.ubData[0]);

			user_input[LEAD_DISTANCE] = 15.0;
			user_input[STEER] = (-4.0 - car_output[LATERAL_DISTANCE]) * 18;
			user_input[ACCELERATION] = ((60.0 - car_output[SPEED]) / 60.0);
			user_input[BRAKE] = 0.0;
			/*
			if(user_input[ACCELERATION] < 0.0)
			{
				user_input[ACCELERATION] = 0.0;
				user_input[BRAKE] = 60;
			}
			*/

			memcpy(&send_buf[0], &user_input[ACCELERATION], 4);
			memcpy(&send_buf[4], &user_input[BRAKE], 4);
			CAN_vLoadData(0x7FF-0x7FF, (ubyte *)send_buf);
			memcpy(&send_buf[0], &user_input[STEER], 4);
			memcpy(&send_buf[4], &user_input[LEAD_DISTANCE], 4);
			CAN_vLoadData(0x7FF-0x7FE, (ubyte *)send_buf);

			set_delayed_output(0x7FF-0x7FF, get_running_component()->next_release_time - get_running_component()->period + get_running_component()->relative_deadline);
			set_delayed_output(0x7FF-0x7FE, get_running_component()->next_release_time - get_running_component()->period + get_running_component()->relative_deadline);

#ifdef LED_VISIBLE
			led_off(1);
#endif
    	}
        syscall_suspend();
    }
}

static void func_high2(void *arg)
{
	while (1) {
#ifdef LED_VISIBLE
		led_on(2);
		delay_ms_f(3);
		led_off(2);
#endif
		syscall_suspend();
	}
}


static void func_dummy(void *arg)
{
    for (;;) {
    	if (get_running_task()->task_state) {
        	led_on(2);
        	delay_ms_f(100);
        	led_off(2);
        	delay_ms_f(100);
    	}
    	syscall_suspend();
    }
}

static void func_idle(void* arg)
{
    for (;;) {
    	__nop();
    }
}

static void func_idle2(void* arg)
{
    for (;;) {
    	__nop();
    }
}
#endif
