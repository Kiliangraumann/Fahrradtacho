################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Displaysteuerung/Displayanzeige/%.obj: ../Displaysteuerung/Displayanzeige/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --data_model=small --use_hw_mpy=F5 --include_path="C:/Program Files/ccs/ccs_base/msp430/include" --include_path="C:/Users/GRAUMKLI/Desktop/Studienarbeit 2/CCS Varianten/SoftwareLoesung" --include_path="C:/Program Files/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --advice:power="all" --define=__MSP430FR5739__ --define=_MPU_ENABLE -g --c11 --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="Displaysteuerung/Displayanzeige/$(basename $(<F)).d_raw" --obj_directory="Displaysteuerung/Displayanzeige" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


