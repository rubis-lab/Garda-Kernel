/**************************************************************************
**                                                                        *
**  FILE        :  setjmp.h                                               *
**                                                                        *
**  DESCRIPTION :  Include file with prototypes for non-local jump        *
**                 functions                                              *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _SETJMP_H
#define _SETJMP_H       1

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */

#define BUF_SIZ 16

typedef int * jmp_buf[BUF_SIZ];

extern  int setjmp      ( jmp_buf );
extern  void longjmp    ( jmp_buf, int ) __noreturn__;

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _SETJMP_H */
