;***************************************************************************
;**                                                                        *
;**   This file contains (parts of) workarounds for several known          *
;**   functional problems.                                                 *
;**                                                                        *
;**   When a integer pipeline jump instruction which operates on a data    *
;**   register value, is directly followed by a csa instruction, a nop     *
;**   must be inserted                                                     *
;**                                                                        *
;***************************************************************************

;
;       CPU_TC.094 workaround:
;               A NOP instruction is inserted before a csa-instruction
.if @DEF('__CPU_TC094__')
        nop
.endif
