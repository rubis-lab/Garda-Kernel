/**************************************************************************
**                                                                        *
**  FILE        :  string.h                                               *
**                                                                        *
**  DESCRIPTION :  Include file with prototypes of functions for          *
**                 string handling and memory checking/movement           *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _STRING_H
#define _STRING_H       1

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


extern  char *  strcpy   ( char * restrict, const char * restrict );
extern  char *  strncpy  ( char * restrict, const char * restrict, size_t );
extern  char *  strcat   ( char * restrict, const char * restrict );
extern  char *  strncat  ( char * restrict, const char * restrict, size_t );
extern  char *  strchr   ( const char *, int );
extern  char *  strrchr  ( const char *, int );
extern  size_t  strspn   ( const char *, const char * );
extern  size_t  strcspn  ( const char *, const char * );
extern  char *  strpbrk  ( const char *, const char * );
extern  char *  strstr   ( const char *, const char * );
extern  char *  strtok   ( char * restrict, const char * restrict );
extern  int     strcmp   ( const char *, const char * );
extern  int     strncmp  ( const char *, const char *, size_t );
extern  size_t  strlen   ( const char * );
extern  void *  memcpy   ( void * restrict, const void * restrict, size_t );
extern  void *  memmove  ( void *, const void *, size_t );
extern  void *  memchr   ( const void *, int, size_t );
extern  void *  memset   ( void *, int, size_t );
extern  int     memcmp   ( const void *, const void *, size_t );
extern  char *  strerror ( int );
extern  int     strcoll  ( const char *, const char * );
extern  size_t  strxfrm  ( char * restrict, const char * restrict, size_t );


#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _STRING_H */
