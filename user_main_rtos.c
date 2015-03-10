#include "user_main.h"
#if 0
enum user_input_name{ACCEL, BRAKE, LEFT_STEER, RIGHT_STEER, STEER_MODE};
enum torcs_output_name{CC_TRIGGER, LKAS_TRIGGER, SPEED, STEER_VALUE, RPM, YAW_RATE, DISTANCE, PASSED_TIME, TARGET_SPEED, ACCEL_VALUE, TARGET_RPM, IS_RUNNING, WHEEL_SPEED, TARGET_WHEEL_SPEED}; 

static void func_1(void *arg);
static void func_2(void *arg);
static void func_3(void *arg);
static void func_cc(void *arg);
static void func_lkas(void *arg);

static void func_idle(void* arg);

#pragma align 8

DECLARE_HWC(hwc_1,       10, 10);
DECLARE_HWC(gnd,         0,  0);    // ground component, or idle component

DECLARE_SWC(idle,               0,    0,        DEFAULT_STACK_SIZE, ACTIVE)
DECLARE_SWC(swc_1,              5,    20,       DEFAULT_STACK_SIZE, INACTIVE)
DECLARE_SWC(swc_2,              4,    35,       DEFAULT_STACK_SIZE, INACTIVE)
DECLARE_SWC(swc_3,              3,    40,       DEFAULT_STACK_SIZE, INACTIVE)
DECLARE_SWC(swc_4,              2,    50,       DEFAULT_STACK_SIZE, ACTIVE)
DECLARE_SWC(swc_5,              1,    60,       DEFAULT_STACK_SIZE, ACTIVE)
DECLARE_SWC(gnd_idle,           0,    0,        DEFAULT_STACK_SIZE, ACTIVE)

#pragma align restore

void callback(uint32_t swc_id, uint32_t flag)
{
    switch (swc_id) {
        case 1:
            swc_1->active = flag;
            break;
        case 2:
            swc_2->active = flag;
            break;
        case 3:
            swc_3->active = flag;
            break;
        case 4:
            swc_4->active = flag;
            break;
        case 5:
            swc_5->active = flag;
            break;
    }
}

void user_main(void)
{
    printf("Starting HW/SW Components...\n");


    create_hwc(hwc_1);
    create_swc(hwc_1, swc_1,    NULL, func_1,    WORK);
    create_swc(hwc_1, swc_2,    NULL, func_2,    WORK);
    create_swc(hwc_1, swc_3,    NULL, func_3,    WORK);
    create_swc(hwc_1, swc_4,    NULL, func_cc,   WORK);
    create_swc(hwc_1, swc_5,    NULL, func_lkas, WORK);
    create_swc(hwc_1, idle,     NULL, func_idle, IDLE);

    create_hwc(gnd);
    create_swc(gnd,   gnd_idle, NULL, func_idle, IDLE);

    /* Enable timer interrupt */
    printf("Starting The Timer Interrupt...\n");
    init_timer_interrupt();
    set_current_hwc(hwc_1);

    /* only the idle task is running after calling schedule() and before the 1st timer interrupt */

    printf("Starting The Scheduler...\n");


    schedule();
}

static void func_1(void *arg)
{
    for (;;) {
    	if (self()->active) {
        	led_on(0);
        	delay_ms_f(1000);
        	led_off(0);
        	delay_ms_f(1000);
    	}
        syscall_suspend();
    }
}

static void func_2(void *arg)
{
    for (;;) {
    	if (self()->active) {
        	led_on(1);
        	delay_ms_f(10);
        	led_off(1);
        	delay_ms_f(10);
    	}
    	syscall_suspend();
    }
}

static void func_3(void *arg)
{
    for (;;) {
    	if (self()->active) {
        	led_on(2);
        	delay_ms_f(100);
        	led_off(2);
        	delay_ms_f(100);
    	}
    	syscall_suspend();
    }
}

static void func_cc(void *arg)
{
    float torcs_output[14 + 10];
    float user_input[5 + 10];
    CAN_SWObj CC_sensing_1, CC_sensing_2;
    ubyte send_buf[16];

    while (1) {
    	led_toggle(3);
    	delay_ms_f(3);
		//while (!(CAN_ubNewData(1) && CAN_ubNewData(4)));

    	CAN_vGetMsgObj(0, &CC_sensing_1);
		CAN_vReleaseObj(0);
		CAN_vGetMsgObj(2, &CC_sensing_2);
		CAN_vReleaseObj(2);

		torcs_output[CC_TRIGGER] = *((float *)&CC_sensing_1.ubData[0]);
		torcs_output[SPEED] = *((float *)&CC_sensing_1.ubData[4]);
		torcs_output[TARGET_SPEED] = *((float *)&CC_sensing_2.ubData[0]);
		torcs_output[ACCEL_VALUE] = *((float *)&CC_sensing_2.ubData[4]);

		if (torcs_output[CC_TRIGGER] > 0.5) {
			if (user_input[ACCEL] < 0.001)	// first time
				user_input[ACCEL] = torcs_output[ACCEL_VALUE];

			if (torcs_output[SPEED] - torcs_output[TARGET_SPEED] < -torcs_output[TARGET_SPEED]*0.01)
				user_input[ACCEL] += 0.0005;
			else if (torcs_output[SPEED] > torcs_output[TARGET_SPEED])
				user_input[ACCEL] -= 0.001;
		} 
        else {
			user_input[ACCEL] = user_input[BRAKE] = 0.0;
		}

		memcpy(&send_buf[0], &user_input[ACCEL], 4);
		memcpy(&send_buf[4], &user_input[BRAKE], 4);
		CAN_vLoadData(10, (ubyte *)send_buf);


		//delayed_output(10, self()->timer);
        CAN_vTransmit(10);

        syscall_suspend();
    }
}

static void func_lkas(void *arg)
{
    float torcs_output[14 + 10];
    float user_input[5 + 10];
    CAN_SWObj LKAS_sensing;
    ubyte send_buf[8];
    float saved_steering = 0.0;

    while (1) {
    	led_toggle(4);
    	delay_ms_f(3);

        //while (!CAN_ubNewData(1));


		CAN_vGetMsgObj(1, &LKAS_sensing);
		CAN_vReleaseObj(1);

		torcs_output[LKAS_TRIGGER] = *((float *)&LKAS_sensing.ubData[0]);
		torcs_output[STEER_VALUE] = *((float *)&LKAS_sensing.ubData[4]);


		saved_steering = torcs_output[STEER_VALUE];
		if (torcs_output[LKAS_TRIGGER] > 0.5) {
			if (saved_steering > 0.0) {
				if (saved_steering > 1.0)
					user_input[LEFT_STEER] = 1.0;
				else
					user_input[LEFT_STEER] = saved_steering;
				user_input[RIGHT_STEER] = 0.0;
			}
			else if (saved_steering < 0.0) {
				if (saved_steering < -1.0)
					user_input[RIGHT_STEER] = 1.0;
				else
					user_input[RIGHT_STEER] = -saved_steering;
				user_input[LEFT_STEER] = 0.0;
			}
		}
		else {
			user_input[LEFT_STEER] = user_input[RIGHT_STEER] = 0.0;
			user_input[STEER_MODE] = 1.0;
		}

		memcpy(&send_buf[0], &user_input[LEFT_STEER], 4);
		memcpy(&send_buf[4], &user_input[RIGHT_STEER], 4);
		CAN_vLoadData(11, (ubyte *)send_buf);

        CAN_vTransmit(11);
		//delayed_output(11, self()->timer);

        syscall_suspend();
    }
}

static void func_idle(void* arg)
{
    for (;;) {
    	__nop();
    }
}
#endif
