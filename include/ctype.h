/**************************************************************************
**                                                                        *
**  FILE        :  ctype.h                                                *
**                                                                        *
**  DESCRIPTION :  Include file with macros and definitions for functions *
**                 testing characters                                     *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _CTYPE_H
#define _CTYPE_H        1

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */

#define __W     0x01
#define __C     0x02
#define __S     0x04
#define __U     0x08
#define __L     0x10
#define __N     0x20
#define __P     0x40
#define __X     0x80

#define _toupper(_c)    ((_c)-'a'+'A')
#define _tolower(_c)    ((_c)-'A'+'a')

#define __CTYPE_SIZE    257
extern __far    const unsigned char   __ctype[__CTYPE_SIZE];

extern  int     isalpha(int);
extern  int     isupper(int);
extern  int     islower(int);
extern  int     isdigit(int);
extern  int     isxdigit(int);
extern  int     isspace(int);
extern  int     isblank(int);
extern  int     ispunct(int);
extern  int     isalnum(int);
extern  int     isprint(int);
extern  int     isgraph(int);
extern  int     iscntrl(int);
extern  int     isascii(int);
extern  int     toascii(int);
extern  int     toupper(int);
extern  int     tolower(int);

#define isalpha(_c)     ((__ctype+1)[_c]&(__U|__L))
#define isupper(_c)     ((__ctype+1)[_c]&__U)
#define islower(_c)     ((__ctype+1)[_c]&__L)
#define isdigit(_c)     ((__ctype+1)[_c]&__N)
#define isxdigit(_c)    ((__ctype+1)[_c]&(__N|__X))
#define isspace(_c)     ((__ctype+1)[_c]&(__S|__W))
#define isblank(_c)     (((__ctype+1)[_c] + __W)&__S)
#define ispunct(_c)     ((__ctype+1)[_c]&__P)
#define isalnum(_c)     ((__ctype+1)[_c]&(__U|__L|__N))
#define isprint(_c)     ((__ctype+1)[_c]&(__P|__U|__L|__N|__S))
#define isgraph(_c)     ((__ctype+1)[_c]&(__P|__U|__L|__N))
#define iscntrl(_c)     ((__ctype+1)[_c]&(__C|__W))
#define isascii(_c)     ((unsigned)(_c)<=0177)
#define toascii(_c)     ((_c)&0177)

#ifdef __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _CTYPE_H */
