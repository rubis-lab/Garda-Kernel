;***************************************************************************
;**                                                                        *
;**   This file contains (parts of) workarounds for several known          *
;**   functional problems.                                                 *
;**                                                                        *
;**   It must be included directly before a loop instruction               *
;**                                                                        *
;***************************************************************************

;
;       CPU_TC018, CPU_TC030 and CPU_TC031 workaround:
;               An ISYNC instruction is inserted before a loop instruction.
;       
.if @DEF('__CPU_TC018__') || @DEF('__CPU_TC030__') || @DEF('__CPU_TC031__') 
        isync
.endif

;
;       CPU_TC096 workaround:
;               Two NOP instructions inserted before a loop instruction.
;       
.if @DEF('__CPU_TC096__') 
        nop
        nop
.endif  
