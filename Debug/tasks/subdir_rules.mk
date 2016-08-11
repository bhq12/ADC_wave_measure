################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
tasks/pollADC.obj: ../tasks/pollADC.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="C:/StellarisWare/inc" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT/include" --include_path="C:/StellarisWare" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="tasks/pollADC.d" --obj_directory="tasks" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tasks/screenDraw.obj: ../tasks/screenDraw.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="C:/StellarisWare/inc" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT/include" --include_path="C:/StellarisWare" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="tasks/screenDraw.d" --obj_directory="tasks" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


