/**************************************************************************
**                                                                        *
**  FILE        :  complex.h                                              *
**                                                                        *
**  DESCRIPTION :  Complex arithmetic                                     *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _COMPLEX_H
#define _COMPLEX_H      1

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */


/*
 * Several macros which are used to address the real and
 * imaginary pars of a complex.
 * The ISO standard specifies that a complex has the same
 * size and alignment as as a float[2], double[2] or
 * long double[2] array.
 * The first part is the real part, the second part is
 * the imaginary part.
 *
 * This might also have been done using structs, which would
 * have made things more readable. However, it might be
 * possible that a struct has a different alignment and/or
 * size from such an array.
 */

#define __cd_r(z)               (((double *)&(z))[0])
#define __cd_i(z)               (((double *)&(z))[1])
#define __cf_r(z)               (((float *)&(z))[0])
#define __cf_i(z)               (((float *)&(z))[1])
#define __cld_r(z)              (((long double *)&(z))[0])
#define __cld_i(z)              (((long double *)&(z))[1])

/*
 * Macros for the imaginary unit for all types.
 */
#define __imag(c)       (_Pragma("extension isuffix") c ## i _Pragma("extension isuffix restore"))

#pragma nomisrac 19.4
#define complex         _Complex
#define imaginary       _Imaginary
#pragma nomisrac restore
#define _Imaginary_I    (__imag(1.0f))
#define _Complex_I      ((const _Complex float) _Imaginary_I)
#define I               (_Imaginary_I)

#define __CFI           ((const _Complex float)       __imag(1.0f))
#define __CDI           ((const _Complex double)      __imag(1.0))
#define __CLDI          ((const _Complex long double) __imag(1.0l))

extern  double complex          cacos(double complex z);
extern  float complex           cacosf(float complex z);
extern  long double complex     cacosl(long double complex z);
extern  double complex          casin(double complex z);
extern  float complex           casinf(float complex z);
extern  long double complex     casinl(long double complex z);
extern  double complex          catan(double complex z);
extern  float complex           catanf(float complex z);
extern  long double complex     catanl(long double complex z);
extern  double complex          ccos(double complex z);
extern  float complex           ccosf(float complex z);
extern  long double complex     ccosl(long double complex z);
extern  double complex          csin(double complex z);
extern  float complex           csinf(float complex z);
extern  long double complex     csinl(long double complex z);
extern  double complex          ctan(double complex z);
extern  float complex           ctanf(float complex z);
extern  long double complex     ctanl(long double complex z);
extern  double complex          cacosh(double complex z);
extern  float complex           cacoshf(float complex z);
extern  long double complex     cacoshl(long double complex z);
extern  double complex          casinh(double complex z);
extern  float complex           casinhf(float complex z);
extern  long double complex     casinhl(long double complex z);
extern  double complex          catanh(double complex z);
extern  float complex           catanhf(float complex z);
extern  long double complex     catanhl(long double complex z);
extern  double complex          ccosh(double complex z);
extern  float complex           ccoshf(float complex z);
extern  long double complex     ccoshl(long double complex z);
extern  double complex          csinh(double complex z);
extern  float complex           csinhf(float complex z);
extern  long double complex     csinhl(long double complex z);
extern  double complex          ctanh(double complex z);
extern  float complex           ctanhf(float complex z);
extern  long double complex     ctanhl(long double complex z);
extern  double complex          cexp(double complex z);
extern  float complex           cexpf(float complex z);
extern  long double complex     cexpl(long double complex z);
extern  double complex          clog(double complex z);
extern  float complex           clogf(float complex z);
extern  long double complex     clogl(long double complex z);
extern  double                  cabs(double complex z);
extern  float                   cabsf(float complex z);
extern  long double             cabsl(long double complex z);
extern  double complex          cpow(double complex x, double complex y);
extern  float complex           cpowf(float complex x, float complex y);
extern  long double complex     cpowl(long double complex x, long double complex y);
extern  double complex          csqrt(double complex z);
extern  float complex           csqrtf(float complex z);
extern  long double complex     csqrtl(long double complex z);
extern  double                  carg(double complex z);
extern  float                   cargf(float complex z);
extern  long double             cargl(long double complex z);
extern  double                  cimag(double complex z);
extern  float                   cimagf(float complex z);
extern  long double             cimagl(long double complex z);
extern  double complex          conj(double complex z);
extern  float complex           conjf(float complex z);
extern  long double complex     conjl(long double complex z);
extern  double complex          cproj(double complex z);
extern  float complex           cprojf(float complex z);
extern  long double complex     cprojl(long double complex z);
extern  double                  creal(double complex z);
extern  float                   crealf(float complex z);
extern  long double             creall(long double complex z);

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _COMPLEX_H */
