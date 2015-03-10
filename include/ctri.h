/**************************************************************************
**                                                                        *
**  FILE        :  ctri.h                                                 *
**                                                                        *
**  DESCRIPTION :  A set of defines to compile a file suitable for ctri   *
**                 with ctc.  These defines will not always suffice, in   *
**                 which case the file will have to be converted first.   *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#define _sfract __wrap __sfract
#define _fract  __wrap __fract
#define _accum  __wrap __laccum

#define _sat   __sat
#define _circ  __circ

#define _packb  __packb
#define _packhw __packhw

#define _near __near
#define _far  __far
#define _a0   __a0
#define _a1   __a1
#define _a8   __a8
#define _a9   __a9

#define _sfrbit16 __sfrbit16
#define _sfrbit32 __sfrbit32

#define _trap      __trap
#define _interrupt __interrupt
#define _trap_fast      __trap_fast
#define _interrupt_fast __interrupt_fast

#define _enable_ __enable_
#define _bisr_   __bisr_

#define _syscallfunc __syscallfunc

#define _inline inline

#define _bit    __bit

#define _at     __at
#define _atbit  __atbit

/*----------------------------------------------------------------------------
|
|       Intrinsic functions
*/

/* System intrinsics */
#define _enable  __enable
#define _disable __disable
#define _dsync   __dsync
#define _isync   __isync
#define _svlcx   __svlcx
#define _rslcx   __rslcx
#define _syscall __syscall
#define _bisr    __bisr
#define _nop     __nop
#define _debug   __debug

/* System intrinsics, TriCore 2 only */
#define _disable2 __disable2
#define _restore  __restore

/* SFR intrinsics */
#define _mfcr __mfcr
#define _mtcr __mtcr

/* Count leading ... intrinsics */
#define _clz __clz
#define _clo __clo
#define _cls __cls

/* Saturation intrinsics */
#define _satb  __satb
#define _satbu __satbu
#define _sath  __sath
#define _sathu __sathu

/* Absolute value intrinsics */
#define _abss __abss
#define _abs  __abs

/* Coprocessor intrinsics */
#define _parity __parity

/* MinMax intrinsics */
#define _min  __min
#define _minu __minu
#define _mins __mins
#define _max  __max
#define _maxu __maxu
#define _maxs __maxs

/* Extract and Insert intrinsics */
#define _extr   __extr
#define _extru  __extru
#define _insert __insert

/* Insert Bit intrinsics */
#define _ins  __ins
#define _insn __insn

/* Multiply and scale intrinsic */
#define _mulsc __mulsc

/* getbit/putbit intrinsics */
#define _imaskldmst __imaskldmst
#define _putbit     __putbit
#define _getbit     __getbit

/* Fract & Accum type intrinsics */
#define _mulfractlong __mulfractlong_ctri
#define _round16      __round16_ctri
#define _getfract     __getfract_ctri
#define _clssf        __clssf_ctri
#define _shasfracts   __shasfracts_ctri
#define _shafracts    __shafracts_ctri
#define _shaaccum     __shaaccum_ctri

/* Circular type instrinsics */
#define _initcirc     __initcirc

/* Packed datatype intrinsics */
#define _initpackbl   __initpackbl
#define _initpackhwl  __initpackhwl
#define _initpackb    __initpackb
#define _initpackhw   __initpackhw
#define _extractbyte1 __extractbyte1
#define _extractbyte2 __extractbyte2
#define _extractbyte3 __extractbyte3
#define _extractbyte4 __extractbyte4
#define _extracthw1   __extracthw1
#define _extracthw2   __extracthw2
#define _getbyte1     __getbyte1
#define _getbyte2     __getbyte2
#define _getbyte3     __getbyte3
#define _getbyte4     __getbyte4
#define _gethw1       __gethw1
#define _gethw2       __gethw2
#define _insertbyte1  __insertbyte1
#define _insertbyte2  __insertbyte2
#define _insertbyte3  __insertbyte3
#define _insertbyte4  __insertbyte4
#define _inserthw1    __inserthw1
#define _inserthw2    __inserthw2
#define _setbyte1     __setbyte1
#define _setbyte2     __setbyte2
#define _setbyte3     __setbyte3
#define _setbyte4     __setbyte4
#define _sethw1       __sethw1
#define _sethw2       __sethw2

/* Packed datatype intrinsics, TriCore 2 specific */
#define _transpose_hword __transpose_hword
#define _transpose_byte  __transpose_byte
#define _swapmsk         __swapmsk

/* Packed datatype operation intrinsics */
#define _absb  __absb
#define _absh  __absh
#define _abssh __abssh
#define _minb  __minb
#define _minbu __minbu
#define _minh  __minh
#define _minhu __minhu
