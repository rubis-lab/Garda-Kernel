/**************************************************************************
**                                                                        *
**  FILE        :  stdint.h                                               *
**                                                                        *
**  DESCRIPTION :  Integer Types                                          *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _STDINT_H
#define _STDINT_H       1

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */

/*
 * 7.18.1.1 Exact-width integer types
 */
typedef signed   char           int8_t;
typedef unsigned char           uint8_t;
typedef signed   short          int16_t;
typedef unsigned short          uint16_t;
typedef signed   int            int32_t;
typedef unsigned int            uint32_t;
typedef signed   long long      int64_t;
typedef unsigned long long      uint64_t;

/*
 * 7.18.1.2 Minimum-width integer types
 */
typedef signed   char           int_least8_t;
typedef unsigned char           uint_least8_t;
typedef signed   short          int_least16_t;
typedef unsigned short          uint_least16_t;
typedef signed   int            int_least32_t;
typedef unsigned int            uint_least32_t;
typedef signed   long long      int_least64_t;
typedef unsigned long long      uint_least64_t;

/*
 * 7.18.1.3 Fastest minimum-width integer types
 */
typedef signed   char           int_fast8_t;
typedef unsigned char           uint_fast8_t;
typedef signed   short          int_fast16_t;
typedef unsigned short          uint_fast16_t;
typedef signed   int            int_fast32_t;
typedef unsigned int            uint_fast32_t;
typedef signed   long long      int_fast64_t;
typedef unsigned long long      uint_fast64_t;

/*
 * 7.18.1.4 Integer types capable of holding object pointers
 */
typedef signed   long           intptr_t;
typedef unsigned long           uintptr_t;

/*
 * 7.18.1.5 Greatest-width integer types
 */
typedef signed   long long      intmax_t;
typedef unsigned long long      uintmax_t;

#if ! defined __cplusplus || defined __STDC_LIMIT_MACROS

/*
 * 7.18.2.1 Limits of exact-width integer types
 */
#define INT8_MIN                (-INT8_MAX-1)
#define INT8_MAX                (0x7f)
#define UINT8_MAX               (0xffU)

#define INT16_MIN               (-INT16_MAX-1)
#define INT16_MAX               (0x7fff)
#define UINT16_MAX              (0xffffU)

#define INT32_MIN               (-INT32_MAX-1)
#define INT32_MAX               (0x7fffffff)
#define UINT32_MAX              (0xffffffffU)

#define INT64_MIN               (-INT64_MAX-1)
#define INT64_MAX               (0x7fffffffffffffffLL)
#define UINT64_MAX              (0xffffffffffffffffULL)

/*
 * 7.18.2.2 Limits of minimum-width integer types
 */
#define INT_LEAST8_MIN          (-INT_LEAST8_MAX-1)
#define INT_LEAST8_MAX          (0x7f)
#define UINT_LEAST8_MAX         (0xffU)

#define INT_LEAST16_MIN         (-INT_LEAST16_MAX-1)
#define INT_LEAST16_MAX         (0x7fff)
#define UINT_LEAST16_MAX        (0xffffU)

#define INT_LEAST32_MIN         (-INT_LEAST32_MAX-1)
#define INT_LEAST32_MAX         (0x7fffffff)
#define UINT_LEAST32_MAX        (0xffffffffU)

#define INT_LEAST64_MIN         (-INT_LEAST64_MAX-1)
#define INT_LEAST64_MAX         (0x7fffffffffffffffLL)
#define UINT_LEAST64_MAX        (0xffffffffffffffffULL)

/*
 * 7.18.2.3 Limits of fastest minimum-width integer types
 */
#define INT_FAST8_MIN           (-INT_FAST8_MAX-1)
#define INT_FAST8_MAX           (0x7f)
#define UINT_FAST8_MAX          (0xffU)

#define INT_FAST16_MIN          (-INT_FAST16_MAX-1)
#define INT_FAST16_MAX          (0x7fff)
#define UINT_FAST16_MAX         (0xffffU)

#define INT_FAST32_MIN          (-INT_FAST32_MAX-1)
#define INT_FAST32_MAX          (0x7fffffff)
#define UINT_FAST32_MAX         (0xffffffffU)

#define INT_FAST64_MIN          (-INT_FAST64_MAX-1)
#define INT_FAST64_MAX          (0x7fffffffffffffffLL)
#define UINT_FAST64_MAX         (0xffffffffffffffffULL)

/*
 * 7.18.2.4 Limits of integer types capable of holding object pointers
 */
#define INTPTR_MIN              (INT32_MIN)
#define INTPTR_MAX              (INT32_MAX)
#define UINTPTR_MAX             (UINT32_MAX)

/*
 * 7.18.2.5 Limits of greatest-width integer types
 */
#define INTMAX_MIN              (INT64_MIN)
#define INTMAX_MAX              (INT64_MAX)
#define UINTMAX_MAX             (UINT64_MAX)

/*
 * 7.18.3 Limits of other integer types
 */
#define PTRDIFF_MIN             (__PTRDIFF_MIN)
#define PTRDIFF_MAX             (__PTRDIFF_MAX)

#define SIG_ATOMIC_MIN          (INT32_MIN)
#define SIG_ATOMIC_MAX          (INT32_MAX)

#define SIZE_MAX                (__SIZE_MAX)

#ifndef WCHAR_MIN
#define WCHAR_MIN               (__WCHAR_MIN)
#endif
#ifndef WCHAR_MAX
#define WCHAR_MAX               (__WCHAR_MAX)
#endif

#define WINT_MIN                (0)
#define WINT_MAX                (UINT32_MAX)

#endif /* ! defined __cplusplus || defined __STDC_LIMIT_MACROS */

#if ! defined __cplusplus || defined __STDC_CONSTANT_MACROS

/*
 * 7.18.4.1 Macros for minimum-width integer constants
 */
#define INT8_C(value)           (value      )
#define UINT8_C(value)          (value ## U )
#define INT16_C(value)          (value      )
#define UINT16_C(value)         (value ## U )
#define INT32_C(value)          (value      )
#define UINT32_C(value)         (value ## U )
#define INT64_C(value)          (value      ##LL)
#define UINT64_C(value)         (value ## U ##LL)

/*
 * 7.18.4.2 Macros for greatest-width integer constants
 */
#define INTMAX_C(value)         (value      ##LL)
#define UINTMAX_C(value)        (value ## U ##LL)

#endif /* ! defined __cplusplus || defined __STDC_CONSTANT_MACROS */

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _STDINT_H */
