/**************************************************************************
**                                                                        *
**  FILE        :  math.h                                                 *
**                                                                        *
**  DESCRIPTION :  Include file with prototypes for mathematical          *
**                 functions                                              *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _MATH_H
#define _MATH_H 1


#ifdef  __SINGLE_FP__
#   define      HUGE_VAL        (3.40282347E+38F)               /* DBL_MAX  */
#   define      HUGE_VALF       (HUGE_VAL)                      /* FLT_MAX  */
#   define      HUGE_VALL       (HUGE_VAL)                      /* LDBL_MAX */
#else
#   define      HUGE_VAL        (1.7976931348623157E+308)       /* DBL_MAX  */
#   define      HUGE_VALF       (3.40282347E+38F)               /* FLT_MAX  */
#   define      HUGE_VALL       (HUGE_VAL)                      /* LDBL_MAX */
#endif

#ifndef FLT_EVAL_METHOD
#   define      FLT_EVAL_METHOD (0)
#endif

#if     FLT_EVAL_METHOD == 0
typedef float           float_t;
typedef double          double_t;
#elif   FLT_EVAL_METHOD == 1
typedef double          float_t;
typedef double          double_t;
#elif   FLT_EVAL_METHOD == 2
typedef long double     float_t;
typedef long double     double_t;
#else
#   error unsupported floating point evaluation method
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern  double          sin             ( double );
extern  float           sinf            ( float );
extern  long double     sinl            ( long double );
extern  double          cos             ( double );
extern  float           cosf            ( float );
extern  long double     cosl            ( long double );
extern  double          tan             ( double );
extern  float           tanf            ( float );
extern  long double     tanl            ( long double );
extern  double          asin            ( double );
extern  float           asinf           ( float );
extern  long double     asinl           ( long double );
extern  double          acos            ( double );
extern  float           acosf           ( float );
extern  long double     acosl           ( long double );
extern  double          atan            ( double );
extern  float           atanf           ( float );
extern  long double     atanl           ( long double );
extern  double          atan2           ( double, double );
extern  float           atan2f          ( float, float );
extern  long double     atan2l          ( long double, long double );
extern  double          sinh            ( double );
extern  float           sinhf           ( float );
extern  long double     sinhl           ( long double );
extern  double          cosh            ( double );
extern  float           coshf           ( float );
extern  long double     coshl           ( long double );
extern  double          tanh            ( double );
extern  float           tanhf           ( float );
extern  long double     tanhl           ( long double );
extern  double          asinh           ( double );
extern  float           asinhf          ( float );
extern  long double     asinhl          ( long double );
extern  double          acosh           ( double );
extern  float           acoshf          ( float );
extern  long double     acoshl          ( long double );
extern  double          atanh           ( double );
extern  float           atanhf          ( float );
extern  long double     atanhl          ( long double );
extern  double          exp             ( double );
extern  float           expf            ( float );
extern  long double     expl            ( long double );
extern  double          exp2            ( double );
extern  float           exp2f           ( float );
extern  long double     exp2l           ( long double );
extern  double          expm1           ( double );
extern  float           expm1f          ( float );
extern  long double     expm1l          ( long double );
extern  double          frexp           ( double, int * );
extern  float           frexpf          ( float, int * );
extern  long double     frexpl          ( long double, int * );
extern  int             ilogb           ( double );
extern  int             ilogbf          ( float );
extern  int             ilogbl          ( long double );
extern  double          ldexp           ( double, int );
extern  float           ldexpf          ( float, int );
extern  long double     ldexpl          ( long double, int );
extern  double          log             ( double );
extern  float           logf            ( float );
extern  long double     logl            ( long double );
extern  double          log10           ( double );
extern  float           log10f          ( float );
extern  long double     log10l          ( long double );
extern  double          log1p           ( double );
extern  float           log1pf          ( float );
extern  long double     log1pl          ( long double );
extern  double          log2            ( double );
extern  float           log2f           ( float );
extern  long double     log2l           ( long double );
extern  double          logb            ( double );
extern  float           logbf           ( float );
extern  long double     logbl           ( long double );
extern  double          modf            ( double, double * );
extern  float           modff           ( float, float * );
extern  long double     modfl           ( long double, long double * );
#if     __STDC_VERSION__ >= 199901L
extern  double          scalbn          ( double, int );
extern  float           scalbnf         ( float, int );
extern  long double     scalbnl         ( long double, int );
extern  double          scalbln         ( double, long );
extern  float           scalblnf        ( float, long );
extern  long double     scalblnl        ( long double, long );
#endif  /* __STDC_VERSION__ >= 199901L */
extern  double          cbrt            ( double );
extern  float           cbrtf           ( float );
extern  long double     cbrtl           ( long double );
extern  double          fabs            ( double );
extern  float           fabsf           ( float );
extern  long double     fabsl           ( long double );
extern  double          hypot           ( double, double );
extern  float           hypotf          ( float, float );
extern  long double     hypotl          ( long double, long double );
extern  double          pow             ( double, double );
extern  float           powf            ( float, float );
extern  long double     powl            ( long double, long double );
extern  double          sqrt            ( double );
extern  float           sqrtf           ( float );
extern  long double     sqrtl           ( long double );
extern  double          erf             ( double );
extern  float           erff            ( float );
extern  long double     erfl            ( long double );
extern  double          erfc            ( double );
extern  float           erfcf           ( float );
extern  long double     erfcl           ( long double );
extern  double          lgamma          ( double );
extern  float           lgammaf         ( float );
extern  long double     lgammal         ( long double );
extern  double          tgamma          ( double );
extern  float           tgammaf         ( float );
extern  long double     tgammal         ( long double );
extern  double          ceil            ( double );
extern  float           ceilf           ( float );
extern  long double     ceill           ( long double );
extern  double          floor           ( double );
extern  float           floorf          ( float );
extern  long double     floorl          ( long double );
extern  double          nearbyint       ( double );
extern  float           nearbyintf      ( float );
extern  long double     nearbyintl      ( long double );
extern  double          rint            ( double );
extern  float           rintf           ( float );
extern  long double     rintl           ( long double );
extern  long            lrint           ( double );
extern  long            lrintf          ( float );
extern  long            lrintl          ( long double );
#if     __STDC_VERSION__ >= 199901L
extern  long long       llrint          ( double );
extern  long long       llrintf         ( float );
extern  long long       llrintl         ( long double );
#endif  /* __STDC_VERSION__ >= 199901L */
extern  double          round           ( double );
extern  float           roundf          ( float );
extern  long double     roundl          ( long double );
extern  long            lround          ( double );
extern  long            lroundf         ( float );
extern  long            lroundl         ( long double );
#if     __STDC_VERSION__ >= 199901L
extern  long long       llround         ( double );
extern  long long       llroundf        ( float );
extern  long long       llroundl        ( long double );
#endif  /* __STDC_VERSION__ >= 199901L */
extern  double          trunc           ( double );
extern  float           truncf          ( float );
extern  long double     truncl          ( long double );
extern  double          fmod            ( double, double );
extern  float           fmodf           ( float, float );
extern  long double     fmodl           ( long double, long double );
extern  double          remainder       ( double, double );
extern  float           remainderf      ( float, float );
extern  long double     remainderl      ( long double, long double );
extern  double          remquo          ( double, double, int * );
extern  float           remquof         ( float, float, int * );
extern  long double     remquol         ( long double, long double, int * );
#if     __STDC_VERSION__ >= 199901L
extern  double          copysign        ( double, double );
extern  float           copysignf       ( float, float );
extern  long double     copysignl       ( long double, long double );
#endif  /* __STDC_VERSION__ >= 199901L */
extern  double          nan             ( const char * );
extern  float           nanf            ( const char * );
extern  long double     nanl            ( const char * );
extern  double          nextafter       ( double, double );
extern  float           nextafterf      ( float, float );
extern  long double     nextafterl      ( long double, long double );
extern  double          nexttoward      ( double, long double );
extern  float           nexttowardf     ( float, long double );
extern  long double     nexttowardl     ( long double, long double );
extern  double          fdim            ( double, double );
extern  float           fdimf           ( float, float );
extern  long double     fdiml           ( long double, long double );
extern  double          fmax            ( double, double );
extern  float           fmaxf           ( float, float );
extern  long double     fmaxl           ( long double, long double );
extern  double          fmin            ( double, double );
extern  float           fminf           ( float, float );
extern  long double     fminl           ( long double, long double );
extern  double          fma             ( double, double, double );
extern  float           fmaf            ( float, float, float );
extern  long double     fmal            ( long double, long double, long double );
#if     __STDC_VERSION__ >= 199901L     
extern  int             _fpclassify             ( double );
extern  int             _fpclassifyf            ( float );
extern  int             _fpclassifyl            ( long double );
extern  int             _isfinite               ( double );
extern  int             _isfinitef              ( float );
extern  int             _isfinitel              ( long double );
extern  int             _isinf                  ( double );
extern  int             _isinff                 ( float );
extern  int             _isinfl                 ( long double );
extern  int             _isnan                  ( double );
extern  int             _isnanf                 ( float );
extern  int             _isnanl                 ( long double );
extern  int             _isnormal               ( double );
extern  int             _isnormalf              ( float );
extern  int             _isnormall              ( long double );
extern  int             _signbit                ( double );
extern  int             _signbitf               ( float );
extern  int             _signbitl               ( long double );

enum
{
        FP_INFINITE,
        FP_NAN,
        FP_NORMAL,
        FP_SUBNORMAL,
        FP_ZERO
};
#define fpclassify(x)           (__tgmath__fpclassify__1(x))
#define isfinite(x)             (__tgmath__isfinite__1(x))
#define isinf(x)                (__tgmath__isinf__1(x))
#define isnan(x)                (__tgmath__isnan__1(x))
#define isnormal(x)             (__tgmath__isnormal__1(x))
#define signbit(x)              (__tgmath__signbit__1(x))
extern  int             _isgreater              ( double, double );
extern  int             _isgreaterf             ( float, float );
extern  int             _isgreaterl             ( long double, long double );
extern  int             _isgreaterequal         ( double, double );
extern  int             _isgreaterequalf        ( float, float );
extern  int             _isgreaterequall        ( long double, long double );
extern  int             _isless                 ( double, double );
extern  int             _islessf                ( float, float );
extern  int             _islessl                ( long double, long double );
extern  int             _islessequal            ( double, double );
extern  int             _islessequalf           ( float, float );
extern  int             _islessequall           ( long double, long double );
extern  int             _islessgreater          ( double, double );
extern  int             _islessgreaterf         ( float, float );
extern  int             _islessgreaterl         ( long double, long double );
extern  int             _isunordered            ( double, double );
extern  int             _isunorderedf           ( float, float );
extern  int             _isunorderedl           ( long double, long double );
#define isgreater(x,y)          (__tgmath__isgreater__2(x,y))
#define isgreaterequal(x,y)     (__tgmath__isgreaterequal__2(x,y))
#define isless(x,y)             (__tgmath__isless__2(x,y))
#define islessequal(x,y)        (__tgmath__islessequal__2(x,y))
#define islessgreater(x,y)      (__tgmath__islessgreater__2(x,y))
#define isunordered(x,y)        (__tgmath__isunordered__2(x,y))
#endif  /* __STDC_VERSION__ >= 199901L */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* _MATH_H */
