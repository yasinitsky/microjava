ifndef TARGET
$(error TARGET variable is not defined)
endif

TOOLCHAIN_PREFIX_pico = arm-none-eabi
CPU_pico = cortex-m0plus

build: FORCE
	@make -f make/module.mk MODULE=make/targets/$(TARGET) BOARD=$(TARGET) TOOLCHAIN_PREFIX=$(TOOLCHAIN_PREFIX_$(TARGET)) CPU=$(CPU_$(TARGET)) -s build

FORCE: ;