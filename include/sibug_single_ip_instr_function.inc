;***************************************************************************
;**                                                                        *
;**   This file contains (parts of) workarounds for several known          *
;**   functional problems.                                                 *
;**                                                                        *
;**   In case a function consists of a single IP instruction               *
;**   this file needs to be included directly before the return            *
;**                                                                        *
;***************************************************************************

;
;       CPU_TC.048 workaround:
;               A NOP instruction is inserted before a return
.if @DEF('__CPU_TC048__')
        nop
.endif
