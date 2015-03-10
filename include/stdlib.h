/**************************************************************************
**                                                                        *
**  FILE        :  stdlib.h                                               *
**                                                                        *
**  DESCRIPTION :  Include file with prototypes of functions for          *
**                 numeric conversions, storage allocation and exit       *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _STDLIB_H
#define _STDLIB_H       1

#ifdef  __cplusplus
extern "C" {
# define __noreturn__   
#endif  /* defined(__cplusplus) */

#ifndef _SIZE_T_DEF
typedef unsigned int    size_t;
#define _SIZE_T_DEF     1
#endif

#ifdef  __cplusplus
#define NULL    (0)
#else   /* !defined(__cplusplus) */
#define NULL    ((void *) 0)
#endif  /* defined(__cplusplus) */

#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1
#define RAND_MAX        32767


typedef struct  {
                        int quot;
                        int rem;
                } div_t;

typedef struct  {
                        long quot;
                        long rem;
                } ldiv_t;

#if     __STDC_VERSION__ >= 199901L
typedef struct  {
                        long long quot;
                        long long rem;
                } lldiv_t;
#endif



extern  int                     atoi     ( const char * );
extern  long                    atol     ( const char * );
extern  double                  atof     ( const char * );
extern  long                    strtol   ( const char * restrict, char ** restrict, int );
extern  unsigned long           strtoul  ( const char * restrict, char ** restrict, int );
extern  double                  strtod   ( const char * restrict, char ** restrict );
extern  float                   strtof   ( const char * restrict, char ** restrict );
extern  long double             strtold  ( const char * restrict, char ** restrict );
extern  int                     abs      ( int );
extern  long                    labs     ( long );
extern  div_t                   div      ( int, int );
extern  ldiv_t                  ldiv     ( long, long );
extern  int                     rand     ( void );
extern  void                    srand    ( unsigned int );

extern  void *                  calloc   ( size_t, size_t ) __malloc__;
extern  void *                  malloc   ( size_t ) __malloc__;
extern  void *                  realloc  ( void *, size_t ) __malloc__;
extern  void                    free     ( void * ) __malloc__;
extern  void *                  _malloc  ( size_t ) __malloc__;
extern  void *                  _realloc ( void *, size_t ) __malloc__;
extern  void                    _free    ( void * ) __malloc__;
        
/* ISO C99 specific functions that are not available when the -c90 command
 * line option is used.
 */
#if     __STDC_VERSION__ >= 199901L
extern  long long               atoll    ( const char * );
extern  long long               strtoll  ( const char * restrict, char ** restrict, int );
extern  unsigned long long      strtoull ( const char * restrict, char ** restrict, int );
extern  long long               llabs    ( long long );
extern  lldiv_t                 lldiv    ( long long, long long );
#endif


extern  void                    exit     ( int ) __noreturn__;
extern  void                    abort    ( void ) __noreturn__;
extern  int                     atexit   ( void (*)(void) );
extern  void                    _Exit    ( int ) __noreturn__;

extern  char *                  getenv   ( const char * );
extern  int                     system   ( const char * );

extern  void *                  bsearch  ( const void *, const void *, size_t, size_t,
                                           int (*)( const void *, const void * ) );
extern  void                    qsort    ( void *, size_t, size_t,
                                           int (*)( const void *, const void * ) );
    
#ifndef _WCHAR_T
typedef signed short int wchar_t;
#define _WCHAR_T        1
#endif

#define MB_CUR_MAX      (1)

extern  int                     mblen    ( const char *, size_t );
extern  int                     mbtowc   ( wchar_t * restrict, const char * restrict, size_t );
extern  int                     wctomb   ( char *, wchar_t );
extern  size_t                  mbstowcs ( wchar_t * restrict, const char * restrict, size_t );
extern  size_t                  wcstombs ( char * restrict, const wchar_t * restrict, size_t );

#ifdef __DSPC__
/*
 * Supportive functions as mentioned in the document:
 * DSP-C  An extension to ISO/IES IS 9899:1990
 */
extern  __fract                 atofr    ( const char * );
extern  __lfract                atolfr   ( const char * );
extern  __accum                 atoac    ( const char * );
extern  __laccum                atolac   ( const char * );

extern  __fract                 strtofr  ( const char * restrict, char ** restrict );
extern  __lfract                strtolfr ( const char * restrict, char ** restrict );
extern  __accum                 strtoac  ( const char * restrict, char ** restrict );
extern  __laccum                strtolac ( const char * restrict, char ** restrict );
#endif

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _STDLIB_H */
