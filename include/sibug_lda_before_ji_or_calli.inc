;***************************************************************************
;**                                                                        *
;**   This file contains (parts of) workarounds for several known          *
;**   functional problems.                                                 *
;**                                                                        *
;**   In case a load address register instruction is being followed        *
;**   immediately by an indirect jump or call instruction, this file       *
;**   needs to be included directly after the load address register        *
;**   instruction.                                                         *
;**                                                                        *
;***************************************************************************

;
;       TC113_CPU11, TC113_CPU16 and CPU_TC.048 workaround:
;               A NOP instruction is inserted between a LDA, LDDA, LD16A
;               and JI or CALLI instruction directly following it.
.if @DEF('__TC113_CPU11__') || @DEF('__TC113_CPU16__') || @DEF('__CPU_TC048__')
        nop
.endif
