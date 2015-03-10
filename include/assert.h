/**************************************************************************
**                                                                        *
**  FILE        :  assert.h                                               *
**                                                                        *
**  DESCRIPTION :  Include file with prototypes and macros to add         *
**                 diagnostics to programs                                *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#pragma nomisrac 92,19.6
#undef assert
#pragma nomisrac restore

#ifndef _STDIO_H
#include <stdio.h>      /* prototype for 'printf' */
#endif  /* _STDIO_H */

#ifndef _STDLIB_H
#include <stdlib.h>     /* prototype for 'abort' */
#endif  /* _STDLIB_H */

#ifndef NDEBUG

/* The assert macro doesn't use the __func__ macro for the function name as
 * this will increase the amount of data generated.
 */
#define assert(_expr)                                                           \
        ((void) (!(_expr) ?                                                     \
          printf("Assertion failed: (%s) file %s, line %d\n",                   \
                 #_expr, __FILE__, __LINE__), abort() : (void) 0                \
        ))

#else

#define assert(_expr)           ((void) 0)

#endif  /* NDEBUG */
