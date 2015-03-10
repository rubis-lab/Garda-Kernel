;***************************************************************************
;**                                                                        *
;**   This file contains (parts of) workarounds for several known          *
;**   functional problems.                                                 *
;**                                                                        *
;**   It must be included directly after a function entry.                 *
;**                                                                        *
;***************************************************************************

;
;       TC113_CPU14 workaround:
;               To bypass the TC113_CPU14 CPU functional problem a DSYNC 
;               instruction is added right after the function entry point.
;
.if @DEF('__TC113_CPU14__')
        dsync                           ; TC113_CPU14 workaround
;
;       CPU_TC034 and TC113_CPU9 workaround:
;               To bypass the CPU_TC034 CPU functional problem 
;               an ISYNC instruction is added right after a DYSNC instruction.
;               To bypass the TC113_CPU9 CPU functional problem 
;               two NOP instructions are added right after a DYSNC instruction.
;
.if @DEF('__TC113_CPU9__') || @DEF('__CPU_TC034__')
        isync
.endif
;
;       CPU_TC024 workaround:
;               Insert a NOP instruction at the very top of any subroutine 
;               if it was previously beginning with a CALL instruction and 
;               in a  multiple DMU master situation (always the case when 
;               a JTAG debugger is attached or if a PCP is working in 
;               background)
;               
.elif  @DEF('__CPU_TC024__')
        nop
.endif
