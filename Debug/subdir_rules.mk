################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/StellarisWare/inc" --include_path="P:/StellarisWare/boards/ek-lm3s1968" --include_path="P:/git/FRT" --include_path="P:/git/FRT/include" --include_path="P:/StellarisWare" --include_path="P:/StellarisWare/boards/ek-lm3s1968" --include_path="P:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rit128x96x4.obj: ../rit128x96x4.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/StellarisWare/inc" --include_path="P:/StellarisWare/boards/ek-lm3s1968" --include_path="P:/git/FRT" --include_path="P:/git/FRT/include" --include_path="P:/StellarisWare" --include_path="P:/StellarisWare/boards/ek-lm3s1968" --include_path="P:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="rit128x96x4.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: ../startup_ccs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/StellarisWare/inc" --include_path="P:/StellarisWare/boards/ek-lm3s1968" --include_path="P:/git/FRT" --include_path="P:/git/FRT/include" --include_path="P:/StellarisWare" --include_path="P:/StellarisWare/boards/ek-lm3s1968" --include_path="P:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="startup_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

state.obj: ../state.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/StellarisWare/inc" --include_path="P:/StellarisWare/boards/ek-lm3s1968" --include_path="P:/git/FRT" --include_path="P:/git/FRT/include" --include_path="P:/StellarisWare" --include_path="P:/StellarisWare/boards/ek-lm3s1968" --include_path="P:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="state.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


