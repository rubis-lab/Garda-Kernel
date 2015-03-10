/**************************************************************************
**                                                                        *
**  FILE        :  tgmath.h                                               *
**                                                                        *
**  DESCRIPTION :  Type-generic math                                      *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _TGMATH_H
#define _TGMATH_H       1

#include <math.h>
#include <complex.h>

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */

/* real + complex */
#define acos(x)         (__tgmath_acos_cacos_1(x))
#define asin(x)         (__tgmath_asin_casin_1(x))
#define atan(x)         (__tgmath_atan_catan_1(x))
#define acosh(x)        (__tgmath_acosh_cacosh_1(x))
#define asinh(x)        (__tgmath_asinh_casinh_1(x))
#define atanh(x)        (__tgmath_atanh_catanh_1(x))
#define cos(x)          (__tgmath_cos_ccos_1(x))
#define sin(x)          (__tgmath_sin_csin_1(x))
#define tan(x)          (__tgmath_tan_ctan_1(x))
#define cosh(x)         (__tgmath_cosh_ccosh_1(x))
#define sinh(x)         (__tgmath_sinh_csinh_1(x))
#define tanh(x)         (__tgmath_tanh_ctanh_1(x))
#define exp(x)          (__tgmath_exp_cexp_1(x))
#define log(x)          (__tgmath_log_clog_1(x))
#define pow(x,y)        (__tgmath_pow_cpow_2(x,y))
#define sqrt(x)         (__tgmath_sqrt_csqrt_1(x))
#define fabs(x)         (__tgmath_fabs_cabs_1(x))

/* real only */
#define atan2(x,y)      (__tgmath_atan2__2(x,y))
#define cbrt(x)         (__tgmath_cbrt__1(x))
#define ceil(x)         (__tgmath_ceil__1(x))
#define copysign(x,y)   (__tgmath_copysign__2(x,y))
#define erf(x)          (__tgmath_erf__1(x))
#define erfc(x)         (__tgmath_erfc__1(x))
#define exp2(x)         (__tgmath_exp2__1(x))
#define expm1(x)        (__tgmath_expm1__1(x))
#define fdim(x,y)       (__tgmath_fdim__2(x,y))
#define floor(x)        (__tgmath_floor__1(x))
#define fma(x,y,z)      (__tgmath_fma__3(x,y,z))
#define fmax(x,y)       (__tgmath_fmax__2(x,y))
#define fmin(x,y)       (__tgmath_fmin__2(x,y))
#define fmod(x,y)       (__tgmath_fmod__2(x,y))
#define frexp(x,y)      (__tgmath_frexp__1(x,y))
#define hypot(x,y)      (__tgmath_hypot__2(x,y))
#define ilogb(x)        (__tgmath_ilogb__1(x))
#define ldexp(x,y)      (__tgmath_ldexp__1(x,y))
#define lgamma(x)       (__tgmath_lgamma__1(x))
#define llrint(x)       (__tgmath_llrint__1(x))
#define llround(x)      (__tgmath_llround__1(x))
#define log10(x)        (__tgmath_log10__1(x))
#define log1p(x)        (__tgmath_log1p__1(x))
#define log2(x)         (__tgmath_log2__1(x))
#define logb(x)         (__tgmath_logb__1(x))
#define lrint(x)        (__tgmath_lrint__1(x))
#define lround(x)       (__tgmath_lround__1(x))
#define nearbyint(x)    (__tgmath_nearbyint__1(x))
#define nextafter(x,y)  (__tgmath_nextafter__2(x,y))
#define nexttoward(x,y) (__tgmath_nexttoward__1(x,y))
#define remainder(x,y)  (__tgmath_remainder__2(x,y))
#define remquo(x,y,z)   (__tgmath_remquo__2(x,y,z))
#define rint(x)         (__tgmath_rint__1(x))
#define round(x)        (__tgmath_round__1(x))
#define scalbn(x,y)     (__tgmath_scalbn__1(x,y))
#define scalbln(x,y)    (__tgmath_scalbln__1(x,y))
#define tgamma(x)       (__tgmath_tgamma__1(x))
#define trunc(x)        (__tgmath_trunc__1(x))

/* complex only */
#define carg(x)         (__tgmath__carg_1(x))
#define cimag(x)        (__tgmath__cimag_1(x))
#define conj(x)         (__tgmath__conj_1(x))
#define cproj(x)        (__tgmath__cproj_1(x))
#define creal(x)        (__tgmath__creal_1(x))

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _TGMATH_H */
