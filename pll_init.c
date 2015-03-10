/*
 * pll_init.c
 *
 *  Created on: 22.09.2009
 *      Author: schrape
 */
#include <stdint.h>
#pragma optimize O3
#pragma tradeoff 0
#pragma immediate_in_code
#include "intrinsic.h"

int pll_init(void)
{
#if defined(__TC1797__)	// 20MHz/2*72/4 = 180MHz
    ///  -----------------------------------------------------------------------
    ///  Clock System:
    ///  -----------------------------------------------------------------------
    ///  - external clock frequency: 20,00 MHz
    ///  - input divider (P): 2
    ///  - PLL operation (VCOBYP = 0)
    ///  - VCO range: 700 MHz - 800 MHz
    ///  - feedback divider (N): 72
    ///  - the VCO output frequency is: 720,00 MHz
    ///  - output divider (K): 4
    ///  - LMB clock: 180,00 MHz
    ///  - the ratio fcpu /ffpi is  2 / 1
    ///  - the ratio fcpu /flmb is  1 / 1
    ///  - the ratio fcpu /fpcp is  1 / 1
    ///  - system clock: 90,00 MHz

    const int fOSC=20;   /* external clock frequency: (default = 20MHz) */
    const int N=72; 	/* PLL N-Divider (default = 72)*/
    const int P=2; 	    /* PLL P-Divider Selection (default = 2) */
    const int K1=3; 	/* PLL K-Divider Selection (default = 3) */
    const int K2=4; 	/* PLL K-Divider Selection (default = 4) */
    const int FPIDIV=1; /* FPI Bus Frequency Select (default = Ratio fCPU/fFPI is 2/1) */
    const int LMBDIV=0; /* LMB Frequency Select (default = Ratio fCPU/fLMB is 1/1) */
    const int PCPDIV=0; /* PCP Frequency Select (default = Ratio fCPU/fPCP is 1/1) */

    endinit_clear(ENDINIT_DEFAULT);
    SCU_OSCCON.B.OSCVAL = fOSC/2.5 - 1;	 // configure watchDog timer to run at about 2.5MHz
    SCU_OSCCON.B.OSCRES = 1;			 // reset the watchdog
    endinit_set(ENDINIT_DEFAULT);
    while (SCU_OSCCON.B.PLLLV && SCU_OSCCON.B.PLLHV);  // or wait about 200 clocks 32*10MHz/2.5MHz

    unsigned k2div = __min(129, N*K1/P)-1;
    endinit_clear(ENDINIT_DEFAULT);
    SCU_CCUCON0.U         = PCPDIV<<24 | LMBDIV<<8 | FPIDIV;
    SCU_PLLCON1.B.K1DIV   = (K1-1);
    while (!SCU_PLLSTAT.B.K1RDY);
    SCU_PLLCON0.B.VCOBYP  = 1;  	 // set VCO bypass => enter Prescaler mode K1 f=fOSC/K1  ; __storebit(SCU_PLLCON0,0,1)
    while (!SCU_PLLSTAT.B.VCOBYST);

    SCU_TRAPDIS.B.SYSVCOLCKT = 1;	 // NMI trap generation for the VCO Lock should be disabled.
    SCU_PLLCON0.U =  0x00050021 | (N-1)<<9 | (P-1)<<24;;  // set P,N divider, connect OSC
    SCU_PLLCON1.B.K2DIV = k2div; // The first target frequency of the Normal Mode should beselected in a way that it matches or is only slightly higher as the one used in the Prescaler Mode.
    endinit_set(ENDINIT_DEFAULT);
    while (SCU_PLLSTAT.B.VCOLOCK == 0);     // wait for LOCK

    endinit_clear(ENDINIT_DEFAULT);

    for (k2div -= __max(k2div/2,1); k2div > (K2-1); k2div -= __max(k2div/2,1)) {
        __nop();
        __nop();
        __nop();  // Between the update of two K2-Divider
        __nop();
        __nop();
        __nop();  // values 6 cycles of fPLL should be waited.
        SCU_PLLCON1.B.K2DIV = k2div;
    }
    SCU_PLLCON1.B.K2DIV = K2-1;

    SCU_TRAPDIS.B.SYSVCOLCKT = 1;	// enable again NMI trap generation
    SCU_PLLCON0.B.VCOBYP  =  0;     // reset VCO bypass
    endinit_set(ENDINIT_DEFAULT);

#else
#error "__<Derivative>__ not yet implemented"
#endif
   return 0;
}
