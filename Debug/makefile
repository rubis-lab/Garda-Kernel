################################################################################
# Automatically-generated file. Do not edit!
################################################################################

PROJ 	= Garda
PRODDIR = C:\Program Files (x86)\TASKING\TriCore v4.1r1\ctc

-include "..\makefile.init"

all :

-include "subdir.mk"
-include "..\makefile.defs"

PCP_FILES :=
EXT_LIBRARIES =

all : "Garda.elf"

"Garda.elf" : $(OBJ_FILES) $(EXT_LIBRARIES) ".Garda.elf.opt"
	@echo Linking to ${@F}
	@"${PRODDIR}\bin\cctc" -f ".Garda.elf.opt"

".Garda.elf.opt" : .refresh
	@argfile ".Garda.elf.opt" -o "Garda.elf" $(OBJ_FILES) $(EXT_LIBRARIES) $(PCP_FILES)  -Ctc1797 -t -I"C:\Users\Rubis\Desktop\workspace_garda_CPS_Demo\workspace_garda\Garda_origin" "../Garda.lsl" -Wl-OtxycL --no-map-file -Wl--map-file="${PROJ}.mapxml":XML -Wl-mcrfiklSmNOduQ -Wl--error-limit=42 -g -Wl--dep-file=".Garda.elf.d" -Wl--make-target="Garda.elf"
DEPENDENCY_FILES += ".Garda.elf.d"
-include $(DEPENDENCY_FILES)

$(EXT_LIBRARIES) : .dummy

GENERATED_FILES += "Garda.elf" "Garda.mapxml" "Garda.mdf" ".Garda.elf.opt" ".Garda.elf.d"
-include "..\makefile.targets"


clean : ".clean.opt"
	@echo Cleaning
	@"${PRODDIR}\bin\rm" -f -m ".clean.opt"

".clean.opt" : .refresh
	@argfile ".clean.opt" $(GENERATED_FILES)

GENERATED_FILES += ".clean.opt"


.PHONY : .dummy .refresh
