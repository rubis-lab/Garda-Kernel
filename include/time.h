/**************************************************************************
**                                                                        *
**  FILE        :  time.h                                                 *
**                                                                        *
**  DESCRIPTION :  Include file with prototypes and macros for            *
**                 manipulating time.                                     *
**                 The low level time routine clock() strongly depends on *
**                 the hardware (e.g. RTC-hardware), so this routine may  *
**                 have to be customised. To determine the time in        *
**                 seconds, the value returned by clock() should be       *
**                 divided by the value of the macro CLOCKS_PER_SEC.      *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _TIME_H
#define _TIME_H 1

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */


#ifndef _SIZE_T_DEF
typedef unsigned int    size_t;
#define _SIZE_T_DEF     1
#endif


#if __STDC_VERSION__ > 199409
typedef unsigned long long      clock_t;
#else
typedef unsigned long   clock_t;
#endif
typedef unsigned long   time_t;

#define TIME_MAX (time_t)(-1)
#define TIME_MIN (time_t)(0)

/* starting point for calendar times
 * time is measured in seconds since 
 * 1 January 1970 
 */
#define _BIAS_TIME ((70 * 365LU + 17) * 86400)

#ifdef  __cplusplus
#define NULL    (0)
#else   /* !defined(__cplusplus) */
#define NULL    ((void *) 0)
#endif  /* defined(__cplusplus) */

#ifndef CLOCKS_PER_SEC
# define CLOCKS_PER_SEC  ((clock_t)__clocks_per_sec)    /* resolution of clock() */
#endif
extern  clock_t __far           __clocks_per_sec;


#ifndef _STRUCT_TM
#define _STRUCT_TM      1

struct tm
{
        int     tm_sec;         /* seconds after the minute - [0, 59]   */
        int     tm_min;         /* minutes after the hour - [0, 59]     */
        int     tm_hour;        /* hours since midnight - [0, 23]       */
        int     tm_mday;        /* day of the month - [1, 31]           */
        int     tm_mon;         /* months since January - [0, 11]       */
        int     tm_year;        /* year since 1900                      */
        int     tm_wday;        /* days since Sunday - [0, 6]           */
        int     tm_yday;        /* days since January 1 - [0, 365]      */
        int     tm_isdst;       /* Daylight Saving Time flag            */
};

#endif /*_STRUCT_TM */

extern  char      * asctime(const struct tm *);
extern  char      * ctime(const time_t *);
extern  double      difftime(time_t, time_t);
extern  struct tm * gmtime(const time_t *);
extern  struct tm * localtime(const time_t *);
extern  time_t      time(time_t *);
extern  time_t      mktime(struct tm *);
extern  clock_t     clock(void);
extern  void        _timer_start(void);         /* start timer */
extern  clock_t     _timer_stop(void);          /* stop timer, return elapsed time */
extern  size_t      strftime(char * restrict, size_t, const char * restrict,
                             const struct tm * restrict);

extern  void        _stime(time_t *);           /* sets system time */
extern  int         _tzset(const char *);       /* sets time zone */

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _TIME_H */
