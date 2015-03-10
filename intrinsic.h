/*!
 \verbatim
 ******************************************************************************
 Copyright (c) Infineon Technologies AG 2010.
 ******************************************************************************
 Infineon Technologies
 Am Campeon 1-12
 85579 Neubiberg
 Germany
 Tel.   : 0 800 951 951 951 (Germany)
 E-mail : support@infineon.com
 Website: http://www.infineon.com/support
 ******************************************************************************
 \endverbatim
 ******************************************************************************
 */
/*!
 ******************************************************************************
 \file     intrinsic.h
 \brief    Implementation and Declaration of intrinsic functions
 \author   Martin Schrape
 \version  0.2
 \date     2010-03-18
 ******************************************************************************
 */
#ifndef INTRINSIC_H_
#define INTRINSIC_H_

#include <sfr/regtc1797.sfr>

/* To define number of interrupt sources
 * The number of of arbitration cycle depends on the number of interrupt
 * sources that are used. The interrupt latency can be reduced when the
 * arbitration cycle, i.e. the number of sources, are reduced
 * \code __mtcr(ICR, INTERRUPT_SOURCES_63);
 */
#define INTERRUPT_SOURCES_255 (0<<24)
#define INTERRUPT_SOURCES_63 (1<<24)
#define INTERRUPT_SOURCES_15 (2<<24)
#define INTERRUPT_SOURCES_3 (3<<24)

#ifndef NDEBUG
#if defined(__CTC__)
#define INITIO(port)    {port##_IOCR0.U = 0x80808080; \
    port##_IOCR4.U = 0x80808080; \
    port##_OMR.U = 0xFF;}
#define SETIO(port,pin)   port##_OMR.U = 1<<(pin)
#define RESETIO(port,pin) SETIO(port,(pin)+16)
#define TOGGLEIO(port,pin) port##_OMR.U = (0x10001)<<(pin)
#elif defined(__CPCP__)
#define SETIO(port,pin)  __asm(".include 'regtc1797.def'     \n\t"  \
    "ldl.iu r0,@HI(1<<" #pin ")   \n\t"  \
    "ldl.il r0,@LO(1<<" #pin ")   \n\t"  \
    "ldl.iu r1,@HI(" #port "_OMR) \n\t"  \
    "ldl.il r1,@LO(" #port "_OMR) \n\t"  \
    "st.if  [r1],0,size=32"      \
  :::"r1","r0");
#define RESETIO(port,pin) SETIO(port,pin+16)
#define TOGGLEIO(port,pin)  __asm(".include 'regtc1797.def'     \n\t"  \
    "ldl.iu r0,@HI(0x10001<<" #pin ")   \n\t"  \
    "ldl.il r0,@LO(0x10001<<" #pin ")   \n\t"  \
    "ldl.iu r1,@HI(" #port "_OMR) \n\t"  \
    "ldl.il r1,@LO(" #port "_OMR) \n\t"  \
    "st.if  [r1],0,size=32"      \
  :::"r1","r0");
#endif
#else
#define INITIO(port)     ((void) 0)
#define SETIO(port,pin)   ((void) 0)
#define RESETIO(port,pin) ((void) 0)
#define TOGGLEIO(port,pin) ((void) 0)
#endif

//!  TriCore context structure
typedef union {
    struct {
        uint32_t pcxi; //!< upper context PCXI
        uint32_t psw; //!< upper context PSW
        void * a10; //!< upper context A10 (SP)
        void * a11; //!< upper context A11 (RA)
        uint32_t d8; //!< upper context D8
        uint32_t d9; //!< upper context D9
        uint32_t d10; //!< upper context D10
        uint32_t d11; //!< upper context D11
        uint32_t a12; //!< upper context A12
        uint32_t a13; //!< upper context A13
        uint32_t a14; //!< upper context A14
        uint32_t a15; //!< upper context A15
        uint32_t d12; //!< upper context D12
        uint32_t d13; //!< upper context D13
        uint32_t d14; //!< upper context D14
        uint32_t d15; //!< upper context D15
    } u; //!< upper context
    struct {
        uint32_t pcxi; //!< lower context PCXI
        void (*pc)(void*); //!< lower context saved PC
        uint32_t a2; //!< lower context A2
        uint32_t a3; //!< lower context A3
        uint32_t d0; //!< lower context D0
        uint32_t d1; //!< lower context D1
        uint32_t d2; //!< lower context D2
        uint32_t d3; //!< lower context D3
        void * a4; //!< lower context A4
        uint32_t a5; //!< lower context A5
        uint32_t a6; //!< lower context A6
        uint32_t a7; //!< lower context A7
        uint32_t d4; //!< lower context D4
        uint32_t d5; //!< lower context D5
        uint32_t d6; //!< lower context D6
        uint32_t d7; //!< lower context D7
    } l; //!< lower context
} context_t;

#if defined(__GNU__)
#define __asm(x) __asm__ volatile(x)
#endif


#define STOREBIT(addr,bpos,b)   __asm("st.t "  #addr "+(" #bpos "/8):" #bpos "%%8,#" #b)
#define __STOREBIT(addr,bpos,b)   __asm("st.t %0:%1,#%2":"i"(addr),"i"(bpos),"i"(b))


#if defined(__TC131__)
/*! Save ICR register and disable interrupts
 \return ICR register
 \note This function is compatible to an instruction in the TC1.6 core
 */
inline uint32_t disable_and_save(void) {
    uint32_t result;
    result = __mfcr(ICR);
    __disable();
    return result; // compliant to CPU_TC.083
}
/*! Restore ICR register
 \param[in] ie ICR register
 \note This function is compatible to an instruction in the TC1.6 core
 */
inline void restore(uint32_t ie) {
    __mtcr(ICR, ie);
}
#endif

/*
 * __endinit endinit
 * A fast __endinit_clear implementation
 * After cstart WDT_CON0.U = 0xFFFC0003
 * WDT_CON1.U = 0x00000008
 */
//! extern declaration of _endinit_clear(void) implemented in cstart.c
extern void _endinit_clear(void);

//! extern declaration of _endinit_set(void) implemented in cstart.c
extern void _endinit_set(void);

// default after power on
#define ENDINIT_DEFAULT  (0xFFFC<<16|0x00<<8|0xF<<4|0x2<<2|1)

//! Fast implementation of to clear the endinit bit
inline void endinit_clear(int x) //!< [in] e.g. ENDINIT_DEFAULT
{
    WDT_CON0.U = x;
    x &= -16L;
    x |= 2;
    WDT_CON0.U = x;
    WDT_CON0.U; // dummy read required;
}

//! Fast implementation of to set the endinit bit
inline void endinit_set(int x) //!< [in] e.g. ENDINIT_DEFAULT
{
    x -= 1;
    WDT_CON0.U = x;
    x &= -16L;
    x |= 3;
    WDT_CON0.U = x;
}

//! Insert NEZ.A instruction
inline uint32_t neza(void *p) {
    int ret;
    __asm("nez.a %0,%1":"=d"(ret):"a"(p));
    return ret;
}

//! Find the maximum value in an uint16_t array
inline uint16_t ixmaxu16(uint16_t *array, //!< [in] array pointer
        unsigned n, //!< [in] number of elements
        uint32_t *indexp) //!< [out] index to maximum value
{
    uint16_t value;
    uint64_t e;

    __asm(""
            " jz.t   %3:0,*+12  ; if n is odd jump +12              \n"
            " mov16  %1.0,#1    ; maximum index 0, working index 1  \n"
            " ld.hu  %1.1,[%2+] ; maximum value is 1st element      \n"
            " j16    *+6        ; jump +6                           \n"
            " mov16  %1.0,#0    ; maximum index 0, working index 0  \n"
            " mov16  %1.1,#0    ; maximum value is UINT_MIN         \n"
            " sh     %3,#-1     ; n = n/2                           \n"
            " mov.a  a15,%3     ;                                   \n"
            " add.a  a15,#-1    ; n -=1                             \n"
            " ld.w   d15,[%2+]  ; Load two next array elements      \n"
            " ixmax.u  %1,%1,d15  ; Find max (IP pipeline)          \n"
            " ld16.w d15,[%2+]  ; Load two next array elements (LS) \n"
            " loop   a15,*-6    ; loop (LP)                         \n"
            " jz16.a %4,*+8     ; if indexp==NULL jump +8           \n"
            " extr.u %1.0,%1.0,#16,#16  ; extract index             \n"
            " st16.h [%4],%1.0  ; *indexp = maximum index           \n"
            " mov    %0,%1.1    ; value = maximum value             \n"
            :"=d"(value),"=&e"(e):"a"(array),"d"(n),"a"(indexp):"a15","d15");
    return value;
}

//! Find the minimum value in an uint16_t array
inline uint16_t ixminu16(uint16_t *array, //!< [in] array pointer
        unsigned n, //!< [in] number of elements
        uint32_t *indexp) //!< [out] index to maximum value
{
    uint16_t value;
    uint64_t e;

    __asm(""
            " jz.t   %3:0,*+12  ; if n is odd jump +12              \n"
            " mov16  %1.0,#1    ; minimum index 0, working index 1  \n"
            " ld.hu  %1.1,[%2+] ; minimum value is 1st element      \n"
            " j16    *+6        ; jump +6                           \n"
            " mov16  %1.0,#0    ; minimum index 0, working index 0  \n"
            " mov16  %1.1,#-1   ; minimum value is UINT_MAX         \n"
            " sh     %3,#-1     ; n = n/2                           \n"
            " mov.a  a15,%3     ;                                   \n"
            " add.a  a15,#-1    ; n -=1                             \n"
            " ld.w   d15,[%2+]  ; Load two next array elements      \n"
            " ixmin.u %1,%1,d15  ; Find min (IP pipeline)           \n"
            " ld16.w d15,[%2+]  ; Load two next array elements (LS) \n"
            " loop   a15,*-6    ; loop (LP)                         \n"
            " jz16.a %4,*+8     ; if indexp==NULL jump +8           \n"
            " extr.u %1.0,%1.0,#16,#16  ; extract index             \n"
            " st16.h [%4],%1.0  ; *indexp = miniumum index          \n"
            " mov    %0,%1.1    ; value = minimum value             \n"
            :"=d"(value),"=&e"(e):"a"(array),"d"(n),"a"(indexp):"a15","d15");
    return value;
}

//! Find the maximum value in an uint32_t array
inline uint32_t ixmax32(uint32_t *array, //!< [in] array pointer
        const unsigned *n, //!< [in] number of elements
        uint32_t *indexp) //!< [out] index to maximum value
{
    uint32_t value;
    __asm(""
            " mov.d    d0,%1 \n"
            " mov      d14,#0      ;initialize the data reference           \n"
            " ld16.w   d15,[%1]    ;load first value                        \n"
            " max      d14,d14,d15 ;take the max of two values              \n"
            " jlt      d15,d14,*+8 ;check if we need the address of the max \n"
            " mov16.aa a15,%1      ;take the address of the new max         \n"
            " mov16    %0,d15      ; take the value of the new max          \n"
            " ld.w     d15,[+%1]4  ;load next value                         \n"
            " loop     %2,*-14                                              \n"
            " jz16.a   %3,*+10     ; if indexp==NULL jump +8                \n"
            " mov16.d  d15,a15                                              \n"
            " sub16    d15,d0,d15                                           \n"
            " sh16     d15,#2                                               \n"
            " st16.w   [%3],d15  ; *indexp = maxiumum index                 \n"
            :"=d"(value):"a"(array),"a"(n-1),"a"(indexp):"d0","a15","d14","d15");
    return value;
}

//! Insert loop executing NOP instruction cnt times
inline void nops(void *cnt) {
#if defined(__TASKING__)
    __asm(" nop16\n"
            " nop16\n"
            " loop %0,*-4"
            ::"a"(cnt));
#elif defined(__GNU__)
    __asm("0: nop16\n"
            " nop16\n"
            " loop %%0,0b"
            ::"a"(cnt));
#endif
}

//! Insert n NOPs instruction
#define NOPS(n)   __asm(".DUP " #n "\n\tnop16\n\t.ENDM\n")

//! Reset instruction cache
inline void reset_icache(void) {
#if defined(__TC1796__) ||  defined(__TC1766__)
    endinit_clear(ENDINIT_DEFAULT);
    PMI_CON0.U = 2; // Cache bypassed
    PMI_CON1.U = 1; // All cache lines are invalidated
    nops((void*)64);       //  wait while busy
    PMI_CON1.U = 0; // Normal code cache (ICACHE) operation
    PMI_CON0.U = 0; // Cache enabled
    endinit_set(ENDINIT_DEFAULT);
#elif defined(__TC1797__) || defined(__TC1767__)
    PMI_CON1.U = 1;
    while (PMI_CON1.U)
        ;
#else
#error "__<derivative>__ not defined"
#endif
}
//! Enable instruction cache
inline void enable_icache(void) {
#if defined(__TC1797__) || defined(__TC1767__)  ||  defined(__TC1796__)||  defined(__TC1766__)
    endinit_clear(ENDINIT_DEFAULT);
    PMI_CON0.U = 0; // PMI_CON0_CCBYP;
    endinit_set(ENDINIT_DEFAULT);
#else
#error "__<derivative>__ not defined"
#endif
}

//! Disable instruction cache
inline void disable_icache(void) {
#if defined(__TC1797__) || defined(__TC1767__)  ||  defined(__TC1796__)||  defined(__TC1766__)
    endinit_clear(ENDINIT_DEFAULT);
    PMI_CON0.U = 2; // PMI_CON0_CCBYP;
    endinit_set(ENDINIT_DEFAULT);
#else
#error "__<derivative>__ not defined"
#endif
}

//! Convert function pointer to function running uncached (Segment A)
inline void *uncached(void(*f)(void)) {
    return (void*) __insert(10L << 28, (int) f, 0, 28);
}
//! Convert function pointer to function running cached (Segment 8)
inline void *cached(void(*f)(void)) {
    return (void*) __insert(8L << 28, (int) f, 0, 28);
}
/*! Busy delay
 \pre FREQ_CPU_MHZ must be defined
 */
inline void delay_us(uint32_t _microseconds) {
    nops((void *) (_microseconds * FREQ_CPU_MHZ / 2 / 2));
}

/*! Busy delay
 \pre FREQ_CPU_MHZ must be defined
 */

inline void delay_ms_f(float _milliseconds) {

uint32_t x;
x = (_milliseconds*FREQ_CPU_MHZ)/2;

#if defined(__TASKING__)
    __asm( "  mov.u d15,#1000 \n"
            "  mov.a a15,d15  \n"
            "  nop16          \n"
            "  nop16          \n"
            "  loop a15,*-4    \n"
            "  loop %0,*-8   \n"
            ::"a"(x): "a15","d15");
#elif defined(__GNU__)

    __asm("    mov.u %d15,1000 \n"
            "1:  mov.a %a15,%d15  \n"
            "0:  nop              \n"
            "    nop              \n"
            "    loop %a15,0b     \n"
            "    loop %%0,1b      \n"
            ::"a"(_milliseconds*2/FREQ_CPU_MHZ): "d15","a15");
#endif
}
inline void delay_ms(uint32_t _milliseconds) {
#if defined(__TASKING__)
    __asm( "  mov.u d15,#1000 \n"
            "  mov.a a15,d15  \n"
            "  nop16          \n"
            "  nop16          \n"
            "  loop a15,*-4    \n"
            "  loop %0,*-8   \n"
            ::"a"((_milliseconds*FREQ_CPU_MHZ)/2): "a15","d15");
#elif defined(__GNU__)

    __asm("    mov.u %d15,1000 \n"
            "1:  mov.a %a15,%d15  \n"
            "0:  nop              \n"
            "    nop              \n"
            "    loop %a15,0b     \n"
            "    loop %%0,1b      \n"
            ::"a"(_milliseconds*2/FREQ_CPU_MHZ): "d15","a15");
#endif
}

inline void delay_ms_half(uint32_t _milliseconds) {
#if defined(__TASKING__)
    __asm( "  mov.u d15,#1000 \n"
            "  mov.a a15,d15  \n"
            "  nop16          \n"
            "  nop16          \n"
            "  loop a15,*-4    \n"
            "  loop %0,*-8   \n"
            ::"a"((_milliseconds*FREQ_CPU_MHZ)/4): "a15","d15");
#elif defined(__GNU__)

    __asm("    mov.u %d15,1000 \n"
            "1:  mov.a %a15,%d15  \n"
            "0:  nop              \n"
            "    nop              \n"
            "    loop %a15,0b     \n"
            "    loop %%0,1b      \n"
            ::"a"(_milliseconds*2/FREQ_CPU_MHZ): "d15","a15");
#endif
}

/*! Convert context pointer to address pointer
 \param[in] cx context pointer
 \return address pointer
 */
inline context_t *cx_to_addr(uint32_t cx) {
    uint32_t seg_nr = __extru(cx, 16, 4);
    return (context_t *) __insert(seg_nr << 28, cx, 6, 16);
}
/*! Convert address pointer to context pointer
 \param[in] addr address pointer
 \return context pointer
 */
inline uint32_t addr_to_cx(context_t * addr) {
    uint32_t seg_nr, seg_idx;
    seg_nr = __extru((int) addr, 28, 4) << 16;
    seg_idx = __extru((int) addr, 6, 16);
    return seg_nr | seg_idx;
}
/*! Return current process priority number
 \return current priority process number
 */
inline uint32_t cppn(void) {
    return __extru(__mfcr(ICR), 0, 8);
}

#endif /* INTRINSIC_H_ */
