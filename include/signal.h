/**************************************************************************
**                                                                        *
**  FILE        :  signal.h                                               *
**                                                                        *
**  DESCRIPTION :  Include file with prototypes and macros for handling   *
**                 various signals.                                       *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _SIGNAL_H
#define _SIGNAL_H       1

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */


typedef int     sig_atomic_t;
typedef void    signalfunction( int );

#define _NSIG           7 /* one more then last code */

#define SIGINT          1
#define SIGILL          2
#define SIGFPE          3
#define SIGSEGV         4
#define SIGTERM         5
#define SIGABRT         6
#define SIG_DFL         ((void (*)(int))0)
#define SIG_IGN         ((void (*)(int))1)
#define SIG_ERR         ((void (*)(int))-1)

extern  signalfunction *signal(int, signalfunction *);
extern  int raise( int );

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _SIGNAL_H */
