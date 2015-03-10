;***************************************************************************
;**                                                                        *
;**   This file contains (parts of) workarounds for several known          *
;**   functional problems.                                                 *
;**                                                                        *
;**   It must be included directly before divide instructions              *
;**   This workaround must be accompagnied by the workaround which goes    *
;**   directly after divide instructions.                                  *
;**   The d7-register is used and must be preserved until the end of the   *
;**   divide.                                                              * 
;**                                                                        *
;***************************************************************************

.if __UM_USER_1__
.if @DEF('__CPU_TC068__')
        ;;
        ;;      Save interrupt state and disable interrupts
        ;; 
        mfcr            d7,#0xfe2c      ; save ICR in d7
        disable                         ; disable interrupts
.endif
.endif

.if @DEF('__CPU_TC068__')
        nop
        nop
.endif
