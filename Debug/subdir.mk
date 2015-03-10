################################################################################
# Automatically-generated file. Do not edit!
################################################################################

C_FILES += "..\CAN.c"
OBJ_FILES += "CAN.o"
"CAN.o" : "..\CAN.c" ".CAN.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f ".CAN.o.opt"

".CAN.o.opt" : .refresh
	@argfile ".CAN.o.opt" -o "CAN.o" "..\CAN.c" -Ctc1797 -t -I"C:\Users\Rubis\Desktop\workspace_garda_CPS_Demo\workspace_garda\Garda_origin" -Wa-H"sfr/regtc1797.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -H"sfr/regtc1797.sfr" -D__TC1797__=1 -DFREQ_CPU_MHZ=180 --iso=99 --language=-gcc,-volatile,+strings --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O2 --tradeoff=4 --compact-max-size=200 -g --source -c --dep-file=".CAN.o.d" -Wc--make-target="CAN.o"
DEPENDENCY_FILES += ".CAN.o.d"

C_FILES += "..\cstart.c"
OBJ_FILES += "cstart.o"
"cstart.o" : "..\cstart.c" ".cstart.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f ".cstart.o.opt"

".cstart.o.opt" : .refresh
	@argfile ".cstart.o.opt" -o "cstart.o" "..\cstart.c" -Ctc1797 -t -I"C:\Users\Rubis\Desktop\workspace_garda_CPS_Demo\workspace_garda\Garda_origin" -Wa-H"sfr/regtc1797.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -H"sfr/regtc1797.sfr" -D__TC1797__=1 -DFREQ_CPU_MHZ=180 --iso=99 --language=-gcc,-volatile,+strings --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O2 --tradeoff=4 --compact-max-size=200 -g --source -c --dep-file=".cstart.o.d" -Wc--make-target="cstart.o"
DEPENDENCY_FILES += ".cstart.o.d"

C_FILES += "..\kernel.c"
OBJ_FILES += "kernel.o"
"kernel.o" : "..\kernel.c" ".kernel.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f ".kernel.o.opt"

".kernel.o.opt" : .refresh
	@argfile ".kernel.o.opt" -o "kernel.o" "..\kernel.c" -Ctc1797 -t -I"C:\Users\Rubis\Desktop\workspace_garda_CPS_Demo\workspace_garda\Garda_origin" -Wa-H"sfr/regtc1797.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -H"sfr/regtc1797.sfr" -D__TC1797__=1 -DFREQ_CPU_MHZ=180 --iso=99 --language=-gcc,-volatile,+strings --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O2 --tradeoff=4 --compact-max-size=200 -g --source -c --dep-file=".kernel.o.d" -Wc--make-target="kernel.o"
DEPENDENCY_FILES += ".kernel.o.d"

C_FILES += "..\led.c"
OBJ_FILES += "led.o"
"led.o" : "..\led.c" ".led.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f ".led.o.opt"

".led.o.opt" : .refresh
	@argfile ".led.o.opt" -o "led.o" "..\led.c" -Ctc1797 -t -I"C:\Users\Rubis\Desktop\workspace_garda_CPS_Demo\workspace_garda\Garda_origin" -Wa-H"sfr/regtc1797.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -H"sfr/regtc1797.sfr" -D__TC1797__=1 -DFREQ_CPU_MHZ=180 --iso=99 --language=-gcc,-volatile,+strings --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O2 --tradeoff=4 --compact-max-size=200 -g --source -c --dep-file=".led.o.d" -Wc--make-target="led.o"
DEPENDENCY_FILES += ".led.o.d"

C_FILES += "..\MAIN.c"
OBJ_FILES += "MAIN.o"
"MAIN.o" : "..\MAIN.c" ".MAIN.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f ".MAIN.o.opt"

".MAIN.o.opt" : .refresh
	@argfile ".MAIN.o.opt" -o "MAIN.o" "..\MAIN.c" -Ctc1797 -t -I"C:\Users\Rubis\Desktop\workspace_garda_CPS_Demo\workspace_garda\Garda_origin" -Wa-H"sfr/regtc1797.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -H"sfr/regtc1797.sfr" -D__TC1797__=1 -DFREQ_CPU_MHZ=180 --iso=99 --language=-gcc,-volatile,+strings --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O2 --tradeoff=4 --compact-max-size=200 -g --source -c --dep-file=".MAIN.o.d" -Wc--make-target="MAIN.o"
DEPENDENCY_FILES += ".MAIN.o.d"

C_FILES += "..\pll_init.c"
OBJ_FILES += "pll_init.o"
"pll_init.o" : "..\pll_init.c" ".pll_init.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f ".pll_init.o.opt"

".pll_init.o.opt" : .refresh
	@argfile ".pll_init.o.opt" -o "pll_init.o" "..\pll_init.c" -Ctc1797 -t -I"C:\Users\Rubis\Desktop\workspace_garda_CPS_Demo\workspace_garda\Garda_origin" -Wa-H"sfr/regtc1797.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -H"sfr/regtc1797.sfr" -D__TC1797__=1 -DFREQ_CPU_MHZ=180 --iso=99 --language=-gcc,-volatile,+strings --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O2 --tradeoff=4 --compact-max-size=200 -g --source -c --dep-file=".pll_init.o.d" -Wc--make-target="pll_init.o"
DEPENDENCY_FILES += ".pll_init.o.d"

C_FILES += "..\sync_on_halt.c"
OBJ_FILES += "sync_on_halt.o"
"sync_on_halt.o" : "..\sync_on_halt.c" ".sync_on_halt.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f ".sync_on_halt.o.opt"

".sync_on_halt.o.opt" : .refresh
	@argfile ".sync_on_halt.o.opt" -o "sync_on_halt.o" "..\sync_on_halt.c" -Ctc1797 -t -I"C:\Users\Rubis\Desktop\workspace_garda_CPS_Demo\workspace_garda\Garda_origin" -Wa-H"sfr/regtc1797.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -H"sfr/regtc1797.sfr" -D__TC1797__=1 -DFREQ_CPU_MHZ=180 --iso=99 --language=-gcc,-volatile,+strings --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O2 --tradeoff=4 --compact-max-size=200 -g --source -c --dep-file=".sync_on_halt.o.d" -Wc--make-target="sync_on_halt.o"
DEPENDENCY_FILES += ".sync_on_halt.o.d"

C_FILES += "..\user_main.c"
OBJ_FILES += "user_main.o"
"user_main.o" : "..\user_main.c" ".user_main.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f ".user_main.o.opt"

".user_main.o.opt" : .refresh
	@argfile ".user_main.o.opt" -o "user_main.o" "..\user_main.c" -Ctc1797 -t -I"C:\Users\Rubis\Desktop\workspace_garda_CPS_Demo\workspace_garda\Garda_origin" -Wa-H"sfr/regtc1797.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -H"sfr/regtc1797.sfr" -D__TC1797__=1 -DFREQ_CPU_MHZ=180 --iso=99 --language=-gcc,-volatile,+strings --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O2 --tradeoff=4 --compact-max-size=200 -g --source -c --dep-file=".user_main.o.d" -Wc--make-target="user_main.o"
DEPENDENCY_FILES += ".user_main.o.d"

C_FILES += "..\user_main_rtos.c"
OBJ_FILES += "user_main_rtos.o"
"user_main_rtos.o" : "..\user_main_rtos.c" ".user_main_rtos.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f ".user_main_rtos.o.opt"

".user_main_rtos.o.opt" : .refresh
	@argfile ".user_main_rtos.o.opt" -o "user_main_rtos.o" "..\user_main_rtos.c" -Ctc1797 -t -I"C:\Users\Rubis\Desktop\workspace_garda_CPS_Demo\workspace_garda\Garda_origin" -Wa-H"sfr/regtc1797.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -H"sfr/regtc1797.sfr" -D__TC1797__=1 -DFREQ_CPU_MHZ=180 --iso=99 --language=-gcc,-volatile,+strings --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O2 --tradeoff=4 --compact-max-size=200 -g --source -c --dep-file=".user_main_rtos.o.d" -Wc--make-target="user_main_rtos.o"
DEPENDENCY_FILES += ".user_main_rtos.o.d"


GENERATED_FILES += "CAN.o" ".CAN.o.opt" ".CAN.o.d" "CAN.src" "CAN.lst" "cstart.o" ".cstart.o.opt" ".cstart.o.d" "cstart.src" "cstart.lst" "kernel.o" ".kernel.o.opt" ".kernel.o.d" "kernel.src" "kernel.lst" "led.o" ".led.o.opt" ".led.o.d" "led.src" "led.lst" "MAIN.o" ".MAIN.o.opt" ".MAIN.o.d" "MAIN.src" "MAIN.lst" "pll_init.o" ".pll_init.o.opt" ".pll_init.o.d" "pll_init.src" "pll_init.lst" "sync_on_halt.o" ".sync_on_halt.o.opt" ".sync_on_halt.o.d" "sync_on_halt.src" "sync_on_halt.lst" "user_main.o" ".user_main.o.opt" ".user_main.o.d" "user_main.src" "user_main.lst" "user_main_rtos.o" ".user_main_rtos.o.opt" ".user_main_rtos.o.d" "user_main_rtos.src" "user_main_rtos.lst"
