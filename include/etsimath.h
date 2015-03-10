/**************************************************************************
**                                                                        *
**  FILE        :  etsimath.h                                             *
**                                                                        *
**  DESCRIPTION :  Header file to be used in programs that use standard   *
**                 ETSI functions (as intrinsics).                        *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef ETSIMATH_H
#define ETSIMATH_H

#define L_abs(a)        __L_abs(a)
#define L_add(a,b)      __L_add(a,b)
#define L_deposit_h(a)  __L_deposit_h(a)
#define L_deposit_l(a)  __L_deposit_l(a)
#define L_mac(a,b,c)    __L_mac(a,b,c)
#define L_macNs(a,b,c)  __L_macNs(a,b,c)
#define L_msu(a,b,c)    __L_msu(a,b,c)
#define L_msuNs(a,b,c)  __L_msuNs(a,b,c)
#define L_mult(a,b)     __L_mult(a,b)
#define L_negate(a)     __L_negate(a)
#define L_sat(a)        __L_sat(a)
#define L_shl(a,b)      __L_shl(a,b)
#define L_shr(a,b)      __L_shr(a,b)
#define L_shr_r(a,b)    __L_shr_r(a,b)
#define L_sub(a,b)      __L_sub(a,b)
#define abs_s(a)        __abs_s(a)
#define add(a,b)        __add(a,b)
#define div_s(a,b)      __div_s(a,b)
#define extract_h(a)    __extract_h(a)
#define extract_l(a)    __extract_l(a)
#define mac_r(a,b,c)    __mac_r(a,b,c)
#define msu_r(a,b,c)    __msu_r(a,b,c)
#define mult(a,b)       __mult(a,b)
#define mult_r(a,b)     __mult_r(a,b)
#define negate(a)       __negate(a)
#define norm_l(a)       __norm_l(a)
#define norm_s(a)       __norm_s(a)
#define round(a)        __round(a)
#define shl(a,b)        __shl(a,b)
#define shr(a,b)        __shr(a,b)
#define shr_r(a,b)      __shr_r(a,b)
#define sub(a,b)        __sub(a,b)

#endif /* ETSIMATH_H */
