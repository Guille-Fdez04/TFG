################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/MemMang/%.obj: ../FreeRTOS/Source/portable/MemMang/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --include_path="D:/TFG/CodeComposer/MonitorizacionCargaTIVA" --include_path="D:/TFG/CodeComposer/MonitorizacionCargaTIVA/FreeRTOS/Source/include" --include_path="D:/TFG/CodeComposer/MonitorizacionCargaTIVA/FreeRTOS/Source/portable/CCS/ARM_CM4F" --define=ccs="ccs" --define=DEBUG --define=PART_TM4C123GH6PM --define=TARGET_IS_BLIZZARD_RB1 --define=WANT_CMDLINE_HISTORY -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/Source/portable/MemMang/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS/Source/portable/MemMang" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


