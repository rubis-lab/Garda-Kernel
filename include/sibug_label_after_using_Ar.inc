;***************************************************************************
;**                                                                        *
;**   This file contains (parts of) workarounds for several known          *
;**   functional problems.                                                 *
;**                                                                        *
;**   It must be included a label, if an address register is used in the   *
;**   next instruction.                                                    *
;**                                                                        *
;***************************************************************************

;
;       CPU_TC021 workaround:
;       
.if @DEF('__CPU_TC021__')
        nop
.endif
