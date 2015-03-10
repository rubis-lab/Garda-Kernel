

/**************************************************************************
**                                                                        *
**  FILE        :  except.h                                               *
**                                                                        *
**  DESCRIPTION :  Software floating point exception handling             *
**                                                                        *
|*  Copyright 1997-2010 Altium BV
**                                                                        *
**************************************************************************/

#ifndef _EXCEPT_H
#define _EXCEPT_H

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */

/*
 * IEEE-754 Exception handling interface definition
 */

#define _TYPE_SIGNED_CHARACTER          1
#define _TYPE_UNSIGNED_CHARACTER        2
#define _TYPE_SIGNED_SHORT_INTEGER      3
#define _TYPE_UNSIGNED_SHORT_INTEGER    4
#define _TYPE_SIGNED_INTEGER            5
#define _TYPE_UNSIGNED_INTEGER          6
#define _TYPE_SIGNED_LONG_INTEGER       7
#define _TYPE_UNSIGNED_LONG_INTEGER     8
#define _TYPE_FLOAT                     9
#define _TYPE_DOUBLE                    10

#if     __STDC_VERSION__ >= 199901L
#define _TYPE_SIGNED_LLONG_INTEGER      11
#define _TYPE_UNSIGNED_LLONG_INTEGER    12
#endif

typedef unsigned char   _fp_fmt_t;

#define EFINVOP         0x01    /* invalid operation, for instance 0.0/0.0, 0.0*Inf or on a NaN */
#define EFDIVZ          0x02    /* division by zero, for instance 12.5/0.0 (not 0.0/0.0)    */
#define EFOVFL          0x04    /* overflow, when the result of an operation is too large       */
#define EFUNFL          0x08    /* underflow,when the result of an operation is too small       */
#define EFINEXCT        0x10
#define EFALL           0x1f    /* the combination of all the above enlisted exceptions */

typedef unsigned char   _fp_exception_type_t;

#define _OP_ADDITION            1
#define _OP_SUBTRACTION         2
#define _OP_COMPARISON          3
#define _OP_EQUALITY            4
#define _OP_LESS_THAN           5
#define _OP_LARGER_THAN         6
#define _OP_MULTIPLICATION      7
#define _OP_DIVISION            8
#define _OP_CONVERSION          9

typedef unsigned char   _fp_operation_type_t;


typedef union _fp_value_union_t
{
        char            c;
        unsigned char   uc;
        short           s;
        unsigned short  us;
        int             i;
        unsigned int    ui;
        long            l;
        unsigned long   ul;
        float           f;
        double          d;

#if     __STDC_VERSION__ >= 199901L
        long long               ll;
        unsigned long long      ull;
#endif

        /* Make sure this union is always 64 bits even if double is 32 bits
         * since library always contains 64 bit variant
         */
        unsigned char   size64[8];
}
_fp_value_union_t;

        

typedef struct _fp_exception_info_t
{
        _fp_exception_type_t    exception;
        _fp_operation_type_t    operation;
        _fp_fmt_t               source_format;
        _fp_fmt_t               destination_format;
        _fp_value_union_t       operand1;
        _fp_value_union_t       operand2;
        _fp_value_union_t       result;
}
_fp_exception_info_t;


extern  void            _fp_install_trap_handler( void (*) ( _fp_exception_info_t * ) );

extern  int             _fp_get_exception_mask( void );
extern  void            _fp_set_exception_mask( int );

extern  int             _fp_get_exception_status( void );
extern  void            _fp_set_exception_status( int );

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _EXCEPT_H */
