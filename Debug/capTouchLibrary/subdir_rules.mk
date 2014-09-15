################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
capTouchLibrary/CTS_HAL.obj: ../capTouchLibrary/CTS_HAL.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.4/bin/cl430" -vmspx --abi=coffabi --data_model=large -Ooff -g --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/ccs_base/msp430/msp430ware_1_40_00_26/driverlib" --include_path="Z:/git_repos/ECE2049/lab1" --include_path="Z:/git_repos/ECE2049/lab1/capTouchLibrary" --include_path="C:/ti/msp430/MSP430ware_1_90_00_30/driverlib" --include_path="c:/ti/ccsv6/ccs_base/msp430/msp430ware_1_40_00_26/grlib/grlib" --include_path="c:/ti/ccsv6/ccs_base/msp430/msp430ware_1_40_00_26/grlib/fonts" --include_path="c:/ti/ccsv6/ccs_base/msp430/msp430ware_1_40_00_26/driverlib/MSP430F5xx_6xx" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.4/include" --advice:power_severity=suppress --gcc --define=__MSP430F5529__ --diag_warning=225 --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="capTouchLibrary/CTS_HAL.pp" --obj_directory="capTouchLibrary" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

capTouchLibrary/CTS_Layer.obj: ../capTouchLibrary/CTS_Layer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.4/bin/cl430" -vmspx --abi=coffabi --data_model=large -Ooff -g --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/ccs_base/msp430/msp430ware_1_40_00_26/driverlib" --include_path="Z:/git_repos/ECE2049/lab1" --include_path="Z:/git_repos/ECE2049/lab1/capTouchLibrary" --include_path="C:/ti/msp430/MSP430ware_1_90_00_30/driverlib" --include_path="c:/ti/ccsv6/ccs_base/msp430/msp430ware_1_40_00_26/grlib/grlib" --include_path="c:/ti/ccsv6/ccs_base/msp430/msp430ware_1_40_00_26/grlib/fonts" --include_path="c:/ti/ccsv6/ccs_base/msp430/msp430ware_1_40_00_26/driverlib/MSP430F5xx_6xx" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.4/include" --advice:power_severity=suppress --gcc --define=__MSP430F5529__ --diag_warning=225 --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="capTouchLibrary/CTS_Layer.pp" --obj_directory="capTouchLibrary" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


