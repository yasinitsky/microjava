MODULE_TYPE := static_lib

DEPENDENCIES += shared

# acts like map with board as a key and boot2 as a value
BOOT2_pico := w25q080.S

SOURCE_FILES += src/assert.c
SOURCE_FILES += src/bootrom.c
SOURCE_FILES += src/clocks.c
SOURCE_FILES += src/crt0.S
SOURCE_FILES += src/floating_point.c
SOURCE_FILES += src/int_divider.c
SOURCE_FILES += src/memory.c
SOURCE_FILES += src/pll.c
SOURCE_FILES += src/resets.c
SOURCE_FILES += src/xosc.c
SOURCE_FILES += src/boot2/$(BOOT2_$(BOARD))

HEADERS := include

OUTPUT := microjava_rp2040_driver