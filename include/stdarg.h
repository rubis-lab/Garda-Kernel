/**************************************************************************
**                                                                        *
**  FILE        :  stdarg.h                                               *
**                                                                        *
**  DESCRIPTION :  Include file with prototypes and macros for usage with *
**                 variable argument lists                                *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _STDARG_H
#define _STDARG_H       1

typedef char * va_list;

#define va_start(ap,last) ((ap) = __dotdotdot__())
#define __va_size(type)   ((sizeof(type) + 3) & ~ 3u)
#pragma nomisrac 96,19.10       /* type cannot be enclosed in parenthesis */
#define va_arg(ap,type)   (*(type *)(((ap) += __va_size(type)) - __va_size(type)))
#pragma nomisrac restore
#define va_end(ap)        ((void) 0)  
#define va_copy(dest,src) ((dest) = (src))

#endif  /* _STDARG_H */
