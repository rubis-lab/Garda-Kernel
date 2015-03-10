/**************************************************************************
**                                                                        *
**  FILE        :  clock.h                                                *
**                                                                        *
**  DESCRIPTION :  TriCore specific timing functions                      *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _CLOCK_H
#define _CLOCK_H

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */

extern  int setfosc ( int mhz ); 
        /* 
                sets the clock speed the clock uses, in MHz
        */
extern  int getfosc ( void    ); 
        /* 
                get the clock speed the clock uses, in MHz
        */

extern  unsigned long clock_msec        ( void ); 
        /* 
                millisecond timer, wraps after more than 20 years at 100 MHz
        */
extern  unsigned long clock_usec        ( void );
        /* 
                microsecond timer, wraps after about 4294 seconds
        */
extern  unsigned long clock_usec_fast   ( void );
        /* 
                microsecond timer, wraps after about 43 seconds at 100 MHz
        */

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _CLOCK_H */
