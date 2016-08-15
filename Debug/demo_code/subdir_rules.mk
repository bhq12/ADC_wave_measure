################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
demo_code/basic_io.obj: ../demo_code/basic_io.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/StellarisWare/inc" --include_path="P:/StellarisWare/boards/ek-lm3s1968" --include_path="P:/git/FRT" --include_path="P:/git/FRT/include" --include_path="P:/StellarisWare" --include_path="P:/StellarisWare/boards/ek-lm3s1968" --include_path="P:/StellarisWare/utils" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="demo_code/basic_io.pp" --obj_directory="demo_code" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


