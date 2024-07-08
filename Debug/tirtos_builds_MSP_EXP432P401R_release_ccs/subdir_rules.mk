################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1043953633:
	@$(MAKE) --no-print-directory -Onone -f tirtos_builds_MSP_EXP432P401R_release_ccs/subdir_rules.mk build-1043953633-inproc

build-1043953633-inproc: ../tirtos_builds_MSP_EXP432P401R_release_ccs/release.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti_v8_3_0/xdctools_3_51_01_18_core/xs" --xdcpath="C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source;C:/ti/simplelink_msp432p4_sdk_3_40_01_02/kernel/tirtos/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.msp432:MSP432P401R -r debug -c "C:/ti_v8_3_0/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-1043953633 ../tirtos_builds_MSP_EXP432P401R_release_ccs/release.cfg
configPkg/compiler.opt: build-1043953633
configPkg/: build-1043953633


