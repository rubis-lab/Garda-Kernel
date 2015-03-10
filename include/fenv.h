/**************************************************************************
**                                                                        *
**  FILE        :  fenv.h                                                 *
**                                                                        *
**  DESCRIPTION :  Floating-point environment                             *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _FENV_H
#define _FENV_H 1

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */



typedef struct
{
        int     dummy;
}               fenv_t;


typedef int     fexcept_t;
        
#define FE_DIVBYZERO    (1 << 0)
#define FE_INEXACT      (1 << 1)
#define FE_INVALID      (1 << 2)
#define FE_OVERFLOW     (1 << 3)
#define FE_UNDERFLOW    (1 << 4)

#define FE_ALL_EXCEPT   (FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW)

/* #define      FE_DOWNWARD     */
/* #define      FE_TONEAREST    */
/* #define      FE_TOWARDZERO   */
/* #define      FE_UPWARD       */

#define FE_DFL_ENV      ((const fenv_t*) -1)

extern  void    feclearexcept(int excepts);
extern  void    fegetexceptflag(fexcept_t *flagp, int excepts);
extern  void    feraiseexcept(int excepts);
extern  void    fesetexceptflag(const fexcept_t *flagp, int excepts);
extern  int     fetestexcept(int excepts);
extern  int     fegetround(void);
extern  int     fesetround(int round);
extern  void    fegetenv(fenv_t *envp);
extern  int     feholdexcept(fenv_t *envp);
extern  void    fesetenv(const fenv_t *envp);
extern  void    feupdateenv(const fenv_t *envp);

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _FENV_H */
