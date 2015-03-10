#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

enum sched_policy_e {
    SCHED_FIFO, SCHED_RR, SCHED_OTHER
};

//! User mode definition
enum user_e {
    USER0, USER1, SUPER
};
//! Call depth definition
enum call_depth_overflow_e {
    CALL_DEPTH_OVERFLOW_AT_64 = 0,
    CALL_DEPTH_OVERFLOW_AT_32 = 0x40,
    CALL_DEPTH_OVERFLOW_AT_16 = 0x60,
    CALL_DEPTH_OVERFLOW_AT_8 = 0x70,
    CALL_DEPTH_OVERFLOW_AT_4 = 0x78,
    CALL_DEPTH_OVERFLOW_AT_2 = 0x7C,
    CALL_DEPTH_TRAP_EVERY_CALL = 0x7E,
    CALL_DEPTH_OVERFLOW_DISABLED = 0x7F,
};

#define TRUE        1
#define FALSE       0


#define TASK_INACTIVE		0
#define TASK_ACTIVE			1
#define TASK_INVALID_RESULT	2
#define TASK_INF_LOOP		3


#define SYSCALL_SUSPEND     2
#define SYSCALL_RESUME      3
#define SYSCALL_ABORT		4

/* For CAN componentizing */
#define N_MSG				30
#define N_CAN_SLOT			50

// For DualMode (HighPerformance and Trustworthy)
// values for dual_state
#define DUAL_NONE			0
#define DUAL_HIGH			1
#define DUAL_TRUST			2

#define N_SINFO_POOL		20

#endif
