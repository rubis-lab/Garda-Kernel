/**************************************************************************
**                                                                        *
**  FILE        :  wctype.h                                               *
**                                                                        *
**  DESCRIPTION :  Wide character classification and mapping utilities.   *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _WCTYPE_H
#define _WCTYPE_H       1

#include <limits.h>

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */


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

/*
 * A scalar type that can hold values which represent locale-specific
 * character mappings.
 */
typedef unsigned short wctrans_t;

/*
 * A scalar type that can hold values which represent locale-specific
 * character classifications.
 */
typedef unsigned short wctype_t;

/*
 * Wide character classification functions.
 */
extern  int             iswalnum  ( wint_t );
extern  int             iswalpha  ( wint_t );
extern  int             iswblank  ( wint_t );
extern  int             iswcntrl  ( wint_t );
extern  int             iswdigit  ( wint_t );
extern  int             iswgraph  ( wint_t );
extern  int             iswlower  ( wint_t );
extern  int             iswprint  ( wint_t );
extern  int             iswpunct  ( wint_t );
extern  int             iswspace  ( wint_t );
extern  int             iswupper  ( wint_t );
extern  int             iswxdigit ( wint_t );

/*
 * Wide character case-mapping functions.
 */
extern  wint_t          towlower  ( wint_t );
extern  wint_t          towupper  ( wint_t );

/*
 * Extensible wide character classification functions.
 */
extern  wctype_t                wctype    ( const char* );
extern  int             iswctype  ( wint_t, wctype_t );

/*
 * Extensible wide character mapping functions.
 */
extern  wctrans_t       wctrans   ( const char* );
extern  wint_t          towctrans ( wint_t, wctrans_t );

enum
{
/*
 * Values which represent locale-specific character classifications.
 */
        _alnum    = 0x001,
        _alpha    = 0x002,
        _cntrl    = 0x004,
        _digit    = 0x008,
        _graph    = 0x010,
        _lower    = 0x020,
        _print    = 0x040,
        _punct    = 0x080,
        _space    = 0x100,
        _upper    = 0x200,
        _xdigit   = 0x400,
        _blank    = 0x800,
/*
 * Values which represent locale-specific character mappings.
 */
        _to_lower = 0x1000,
        _to_upper = 0x2000
};

#if ! defined __cplusplus

/*
 * Wide character classification macros.
 */
#define iswalnum(wc)    (iswctype(wc, _alnum))
#define iswalpha(wc)    (iswctype(wc, _alpha))
#define iswblank(wc)    (iswctype(wc, _blank))
#define iswcntrl(wc)    (iswctype(wc, _cntrl))
#define iswdigit(wc)    (iswctype(wc, _digit))
#define iswgraph(wc)    (iswctype(wc, _graph))
#define iswlower(wc)    (iswctype(wc, _lower))
#define iswprint(wc)    (iswctype(wc, _print))
#define iswpunct(wc)    (iswctype(wc, _punct))
#define iswspace(wc)    (iswctype(wc, _space))
#define iswupper(wc)    (iswctype(wc, _upper))
#define iswxdigit(wc)   (iswctype(wc, _xdigit))
/*
 * Extensible wide character mapping macros.
 */
#define towlower(wc) (towctrans(wc, _to_lower))
#define towupper(wc) (towctrans(wc, _to_upper))

#endif  /* ! defined(__cplusplus) */

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif /* _WCTYPE_H */
