/**************************************************************************
**                                                                        *
**  FILE        :  malloc.h                                               *
**                                                                        *
**  DESCRIPTION :  Include file with prototypes of functions for          *
**                 memory allocation.                                     *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _MALLOC_H
#define _MALLOC_H

#ifndef _STDLIB_H

#ifdef  __cplusplus
extern "C" {
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


extern  void *        calloc  ( size_t, size_t ) __malloc__;
extern  void *        malloc  ( size_t ) __malloc__;
extern  void *        realloc ( void *, size_t ) __malloc__;
extern  void          free    ( void * ) __malloc__;
extern  void *        _malloc ( size_t ) __malloc__;
extern  void *        _realloc( void *, size_t ) __malloc__;
extern  void          _free   ( void * ) __malloc__;

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _STDLIB_H */

#endif  /* _MALLOC_H */
