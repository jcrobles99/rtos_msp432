################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti_v8_3_0/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS

GEN_OPTS__FLAG := --cmd_file="configPkg/compiler.opt"
GEN_CMDS__FLAG := -l"configPkg/linker.cmd"

ORDERED_OBJS += \
"./Threads.obj" \
"./system_Threads.obj" \
"./Drivers/ADC_MSP432.obj" \
"./Drivers/GPIO_MSP432.obj" \
"./Drivers/INT_MSP432.obj" \
"./Drivers/TIMER32_MSP432.obj" \
"./Drivers/UART_MSP432.obj" \
"./HAL componentes/ADC.obj" \
"./HAL componentes/GPIO.obj" \
"./HAL componentes/TIMER.obj" \
"./HAL componentes/UART.obj" \
"./HAL procesos/Control.obj" \
"./HAL procesos/Control_Plus.obj" \
"./HAL procesos/Imprimir.obj" \
"./aux_files/system_msp432p401r.obj" \
"../aux_files/MSP_EXP432P401R_TIRTOS.cmd" \
-l"ti/display/lib/display.aem4f" \
-l"ti/grlib/lib/ccs/m4f/grlib.a" \
-l"third_party/spiffs/lib/ccs/m4f/spiffs.a" \
-l"ti/drivers/lib/drivers_msp432p401x.aem4f" \
-l"third_party/fatfs/lib/ccs/m4f/fatfs.a" \
-l"ti/dpl/lib/dpl_msp432p401x.aem4f" \
$(GEN_CMDS__FLAG) \
-l"ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Drivers/subdir_vars.mk
-include HAL\ componentes/subdir_vars.mk
-include HAL\ procesos/subdir_vars.mk
-include aux_files/subdir_vars.mk
-include tirtos_builds_MSP_EXP432P401R_release_ccs/subdir_vars.mk
-include subdir_rules.mk
-include Drivers/subdir_rules.mk
-include HAL\ componentes/subdir_rules.mk
-include HAL\ procesos/subdir_rules.mk
-include aux_files/subdir_rules.mk
-include tirtos_builds_MSP_EXP432P401R_release_ccs/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Proyecto_final_eq_v2.out \

EXE_OUTPUTS__QUOTED += \
"Proyecto_final_eq_v2.out" \

BIN_OUTPUTS += \
Proyecto_final_eq_v2.hex \

BIN_OUTPUTS__QUOTED += \
"Proyecto_final_eq_v2.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Proyecto_final_eq_v2.out"

# Tool invocations
Proyecto_final_eq_v2.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti_v8_3_0/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"Proyecto_final_eq_v2.map" -i"C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" -i"C:/ti/simplelink_msp432p4_sdk_3_40_01_02/kernel/tirtos/packages" -i"C:/ti_v8_3_0/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/lib" --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Proyecto_final_eq_v2_linkInfo.xml" --rom_model -o "Proyecto_final_eq_v2.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Proyecto_final_eq_v2.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti_v8_3_0/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armhex"  -o "Proyecto_final_eq_v2.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "Threads.obj" "system_Threads.obj" "Drivers\ADC_MSP432.obj" "Drivers\GPIO_MSP432.obj" "Drivers\INT_MSP432.obj" "Drivers\TIMER32_MSP432.obj" "Drivers\UART_MSP432.obj" "HAL componentes\ADC.obj" "HAL componentes\GPIO.obj" "HAL componentes\TIMER.obj" "HAL componentes\UART.obj" "HAL procesos\Control.obj" "HAL procesos\Control_Plus.obj" "HAL procesos\Imprimir.obj" "aux_files\system_msp432p401r.obj" 
	-$(RM) "Threads.d" "system_Threads.d" "Drivers\ADC_MSP432.d" "Drivers\GPIO_MSP432.d" "Drivers\INT_MSP432.d" "Drivers\TIMER32_MSP432.d" "Drivers\UART_MSP432.d" "HAL componentes\ADC.d" "HAL componentes\GPIO.d" "HAL componentes\TIMER.d" "HAL componentes\UART.d" "HAL procesos\Control.d" "HAL procesos\Control_Plus.d" "HAL procesos\Imprimir.d" "aux_files\system_msp432p401r.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

