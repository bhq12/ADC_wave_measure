################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
list.obj: ../list.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="C:/StellarisWare/inc" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT/include" --include_path="C:/StellarisWare" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="list.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="C:/StellarisWare/inc" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT/include" --include_path="C:/StellarisWare" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

queue.obj: ../queue.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="C:/StellarisWare/inc" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT/include" --include_path="C:/StellarisWare" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="queue.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rit128x96x4.obj: ../rit128x96x4.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="C:/StellarisWare/inc" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT/include" --include_path="C:/StellarisWare" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="rit128x96x4.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: ../startup_ccs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="C:/StellarisWare/inc" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT/include" --include_path="C:/StellarisWare" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="startup_ccs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tasks.obj: ../tasks.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="C:/StellarisWare/inc" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT" --include_path="C:/Users/Brook/workspace_v6_1_3/FRT/include" --include_path="C:/StellarisWare" --include_path="C:/StellarisWare/boards/ek-lm3s1968" --include_path="C:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="tasks.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


