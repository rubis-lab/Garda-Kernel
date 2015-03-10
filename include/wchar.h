/**************************************************************************
**                                                                        *
**  FILE        :  wchar.h                                                *
**                                                                        *
**  DESCRIPTION :  Extended multibute and wide character utilities.       *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _WCHAR_H
#define _WCHAR_H        1

#include <limits.h>
#include <stdio.h>

#ifdef  __cplusplus
extern "C" {
# define __format__(x,y,z)      
#endif  /* defined(__cplusplus) */


/*
 * The unsigned integral type of the result of the sizeof operator.
 */
#ifndef _SIZE_T_DEF
typedef unsigned int    size_t;
#define _SIZE_T_DEF     1
#endif

/*
 * An integral type whose range of values can represent distinct codes for 
 * all members of the largest extended character set specified among the
 * supported locales. The null character shall have the code value zero.
 */
#ifndef _WCHAR_T
typedef signed short int wchar_t;
#define _WCHAR_T        1
#endif

/*
 * An object type that holds the components of a calandar time, called the
 * broken-down time.
 */
#ifndef _STRUCT_TM
#define _STRUCT_TM      1

struct tm
{
        int tm_sec;     /* seconds after the minute - [0, 59] */
        int tm_min;     /* minutes after the hour - [0, 59]   */
        int tm_hour;    /* hours since midnight - [0, 23]     */
        int tm_mday;    /* day of the month - [1, 31]         */
        int tm_mon;     /* months since January - [0, 11]     */
        int tm_year;    /* year since 1900                    */
        int tm_wday;    /* days since Sunday - [0, 6]         */
        int tm_yday;    /* days since January 1 - [0, 365]    */
        int tm_isdst;   /* Daylight Saving Time flag          */
};

#endif /*_STRUCT_TM */

/*
 * Null pointer constant.
 */
#ifndef NULL
#ifdef  __cplusplus
#define NULL    (0)
#else   /* !defined(__cplusplus) */
#define NULL    ((void *) 0)
#endif  /* defined(__cplusplus) */
#endif  /* !defined(NULL) */

/*
 * The minimum value representable by an object of type wchar_t.
 */
#ifndef WCHAR_MIN
#define WCHAR_MIN ((wchar_t) 0)
#endif  /* !defined(WCHAR_MIN) */

/*
 * The maximum value representable by an object of type wchar_t.
 */
#ifndef WCHAR_MAX
#define WCHAR_MAX ((wchar_t) ~ ((wchar_t) 1 << (8*sizeof(wchar_t)-1)))
#endif  /* !defined(WCHAR_MAX) */

/*
 * A wint_t value that does not correspond to any value of the extended 
 * character set. Used by several functions to indicate end-of-file.
 */
#ifndef WEOF
#define WEOF ((wint_t) UINT_MAX)
#endif

/*
 * An integral type that can hold any value of the extended character set 
 * and at least one other value (like WEOF).
 */
#ifndef _WINT_T
typedef unsigned int wint_t;
#define _WINT_T 1
#endif

/* mbstate_t
 *
 * An object type other than an array type that can hold the conversion
 * state information necessary to convert between sequences of multibyte
 * characters and wide characters.
 *
 * When multibyte characters larger than 1 byte are used this struct
 * will be used to store the conversion information when not all the
 * bytes of a particular multibyte character has been read from the
 * source.  In the current implementation multibyte characters are 1
 * byte long (MB_CUR_MAX and MB_LEN_MAX are defined as 1) and this
 * will never occur.  If this implementation changes, please read the
 * note in <stdio.h> about fpos_t
 */

typedef struct
{
        wchar_t         wc_value;       /* wide character value solved so far */
        unsigned short  n_bytes;        /* number of bytes of solved multibyte */
        unsigned short  encoding;       /* encoding rule for wide character <=> multibyte conversion */
} mbstate_t;


#define INIT_MBSTATE_OBJECT(mbs)        \
        do {                            \
                (mbs).wc_value = 0;     \
                (mbs).n_bytes = 0;      \
                (mbs).encoding = 0;     \
        } while (0)
#define IS_INITIAL_MBSTATE(mbs) ((mbs).wc_value == 0 && (mbs).n_bytes == 0 && (mbs).encoding == 0)

/*
 * Formatted wide character input/output functions.
 */
extern  int                     fwprintf  ( FILE * restrict, const wchar_t * restrict, ... ) __format__(wprintf,2,3);
extern  int                     fwscanf   ( FILE * restrict, const wchar_t * restrict, ... ) __format__(wscanf,2,3);
extern  int                     wprintf   ( const wchar_t * restrict, ... ) __format__(wprintf,1,2);
extern  int                     wscanf    ( const wchar_t * restrict, ... ) __format__(wscanf,1,2);
extern  int                     swprintf  ( wchar_t * restrict, size_t, const wchar_t * restrict, ... ) __format__(wprintf,3,4);
extern  int                     swscanf   ( const wchar_t * restrict, const wchar_t * restrict, ... ) __format__(wscanf,2,3);
extern  int                     vfwprintf ( FILE * restrict, const wchar_t * restrict, va_list ) __format__(wprintf,2,0);
extern  int                     vfwscanf  ( FILE * restrict, const wchar_t * restrict, va_list ) __format__(wscanf,2,0);
extern  int                     vwprintf  ( const wchar_t * restrict, va_list ) __format__(wprintf,1,0);
extern  int                     vwscanf   ( const wchar_t * restrict, va_list ) __format__(wscanf,1,0);
extern  int                     vswprintf ( wchar_t * restrict, size_t, const wchar_t * restrict, va_list ) __format__(wprintf,3,0);
extern  int                     vswscanf  ( const wchar_t * restrict, const wchar_t * restrict, va_list ) __format__(wscanf,2,0);

/*
 * Wide character input/output functions.
 */
extern  wint_t                  fgetwc    ( FILE * );
extern  wchar_t *               fgetws    ( wchar_t * restrict, int, FILE * restrict );
extern  wint_t                  fputwc    ( wchar_t, FILE * );
extern  int                     fputws    ( const wchar_t * restrict, FILE * restrict );
extern  wint_t                  getwc     ( FILE * );
extern  wint_t                  getwchar  ( void );
extern  wint_t                  putwc     ( wchar_t, FILE * );
extern  wint_t                  putwchar  ( wchar_t );
extern  wint_t                  ungetwc   ( wint_t, FILE * );
extern  int                     fwide     ( FILE *, int );

/*
 * Wide string numeric conversion functions.
 */
extern  double                  wcstod   ( const wchar_t * restrict, wchar_t ** restrict );
extern  float                   wcstof   ( const wchar_t * restrict, wchar_t ** restrict );
extern  long double             wcstold  ( const wchar_t * restrict, wchar_t ** restrict );
extern  long                    wcstol   ( const wchar_t * restrict, wchar_t ** restrict, int );
extern  unsigned long           wcstoul  ( const wchar_t * restrict, wchar_t ** restrict, int );

/* ISO C99 specific functions that are not available when the -c90 command
 * line option is used.
 */
#if     __STDC_VERSION__ >= 199901L
extern  long long               wcstoll  ( const wchar_t * restrict, wchar_t ** restrict, int );
extern  unsigned long long      wcstoull ( const wchar_t * restrict, wchar_t ** restrict, int );
#endif

/*
 * Wide string copying functions.
 */
extern  wchar_t *               wcscpy  ( wchar_t * restrict, const wchar_t * restrict );
extern  wchar_t *               wcsncpy ( wchar_t * restrict, const wchar_t * restrict, size_t );

/*
 * Wide string concatenation functions.
 */
extern  wchar_t *               wcscat  ( wchar_t * restrict, const wchar_t * restrict );
extern  wchar_t *               wcsncat ( wchar_t * restrict, const wchar_t * restrict, size_t );

/*
 * Wide string comparison functions.
 */
extern  int                     wcscmp  ( const wchar_t *, const wchar_t * );
extern  int                     wcscoll ( const wchar_t *, const wchar_t * );
extern  int                     wcsncmp ( const wchar_t *, const wchar_t *, size_t );
extern  size_t                  wcsxfrm ( wchar_t * restrict, const wchar_t * restrict, size_t );

/*
 * Wide string search functions.
 */
extern  wchar_t *               wcschr  ( const wchar_t *, wchar_t );
extern  size_t                  wcscspn ( const wchar_t *, const wchar_t * );
extern  wchar_t *               wcspbrk ( const wchar_t *, const wchar_t * );
extern  wchar_t *               wcsrchr ( const wchar_t *, wchar_t );
extern  size_t                  wcsspn  ( const wchar_t *, const wchar_t * );
extern  wchar_t *               wcsstr  ( const wchar_t *, const wchar_t * );
extern  wchar_t *               wcstok  ( wchar_t * restrict, const wchar_t * restrict, wchar_t ** restrict );
extern  size_t                  wcslen  ( const wchar_t * );

/*
 * Wide character array functions.
 */
extern  wchar_t *               wmemchr  ( const wchar_t *, wchar_t, size_t );
extern  int                     wmemcmp  ( const wchar_t * restrict, const wchar_t * restrict, size_t );
extern  wchar_t *               wmemcpy  ( wchar_t * restrict, const wchar_t * restrict, size_t );
extern  wchar_t *               wmemmove ( wchar_t *, const wchar_t *, size_t );
extern  wchar_t *               wmemset  ( wchar_t *, wchar_t, size_t );

/*
 * Wide string time conversion function.
 */
extern  size_t                  wcsftime ( wchar_t * restrict, size_t, const wchar_t * restrict, const struct tm * restrict );

/*
 * Single-byte wide character conversion functions.
 */
extern  wint_t                  btowc    ( int );
extern  int                     wctob    ( wint_t );
extern  int                     mbsinit  ( const mbstate_t * );

/*
 * Restartable multibyte/wide character conversion functions.
 */
extern  size_t                  mbrlen   ( const char * restrict, size_t, mbstate_t * restrict );
extern  size_t                  mbrtowc  ( wchar_t * restrict, const char * restrict, size_t, mbstate_t * restrict );
extern  size_t                  wcrtomb  ( char * restrict, wchar_t, mbstate_t * restrict );

/*
 * Restartable multibyte/wide string conversion functions.
 */
extern  size_t                  mbsrtowcs( wchar_t * restrict, const char ** restrict, size_t, mbstate_t * restrict );
extern  size_t                  wcsrtombs( char * restrict, const wchar_t ** restrict, size_t, mbstate_t * restrict );

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif /* _WCHAR_H */
