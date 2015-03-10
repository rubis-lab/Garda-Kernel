/**************************************************************************
**                                                                        *
**  FILE        :  stddef.h                                               *
**                                                                        *
**  DESCRIPTION :  Include file with macros for common use                *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _STDDEF_H
#define _STDDEF_H       1

#ifndef _SIZE_T_DEF
typedef unsigned int    size_t;
#define _SIZE_T_DEF     1
#endif

#ifndef _WCHAR_T
typedef signed short int wchar_t;
#define _WCHAR_T        1
#endif

typedef signed int      ptrdiff_t;

#ifdef  __cplusplus
#define NULL    (0)
#else   /* defined(__cplusplus) */
#define NULL    ((void *) 0)
#endif  /* defined(__cplusplus) */

#ifdef  __cplusplus
#define offsetof( _type, _member )      ((size_t)(__INTADDR__(&((( _type *)0)->_member))))
#else   /* defined(__cplusplus) */
#pragma nomisrac 96,19.10               /* _type and _member cannot be enclosed in parenthesis */
#define offsetof( _type, _member )      ((size_t)(&(( _type *)0)->_member))
#pragma nomisrac restore
#endif  /* defined(__cplusplus) */

#endif  /* _STDDEF_H */
