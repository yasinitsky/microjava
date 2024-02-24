cmake_minimum_required(VERSION 3.12)

include(boards.cmake)

microjava_map_find(rp2040_board_boot2 RP2040_BOOT2 ${MICROJAVA_BOARD})
if(RP2040_BOOT2 STREQUAL "")
    message(FATAL_ERROR "Can't find a 2nd stage bootloader that matches board " ${MICROJAVA_BOARD} ".")
endif()

add_library(microjava_rp2040_driver STATIC  src/crt0.S
                                            src/boot2/${RP2040_BOOT2}
                                            src/bootrom.c
                                            src/floating_point.c
                                            src/clocks.c
                                            src/int_divider.c
                                            src/memory.c
                                            src/resets.c
                                            src/pll.c
                                            src/xosc.c
                                            src/assert.c)

target_include_directories(microjava_rp2040_driver PUBLIC include)
target_link_libraries(microjava_rp2040_driver microjava_shared)