;***************************************************************************
;**                                                                        *
;**   This file contains (parts of) workarounds for several known          *
;**   functional problems.                                                 *
;**                                                                        *
;**   It must be included directly after divide instructions               *
;**   This workaround must be accompagnied by the workaround which goes    *
;**   directly before divide instructions.                                 *
;**   The d7-register is used and must be preserved until the end of the   *
;**   divide.                                                              *
;**                                                                        *
;***************************************************************************

.if __UM_USER_1__
.if @DEF('__CPU_TC068__')
        ;; 
        ;;      Restore interrupt state
        ;;
        jz.t    d7:8,*+8                ; do not enable interrupts when they were disabled
        enable                          
                                        ; the target address for the conditional jump is 
                                        ; directly after the enable instruction (which is 
                                        ; a 32-bit instruction).
                                        ; a label could not be used for the target address
                                        ; since this file can be included more than once 
                                        ; into the same file.
.endif
.endif
