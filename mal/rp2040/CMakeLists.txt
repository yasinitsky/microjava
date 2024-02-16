cmake_minimum_required(VERSION 3.12)

include(${CMAKE_CURRENT_LIST_DIR}/boards.cmake)

microjava_map_find(rp2040_board_boot2 RP2040_BOOT2 ${MICROJAVA_BOARD})
if(RP2040_BOOT2 STREQUAL "")
    message(FATAL_ERROR "Can't find a 2nd stage bootloader that matches board " ${MICROJAVA_BOARD} ".")
endif()

add_library(microjava_mal_mcu OBJECT    crt0.S
                                        mcu_main.c
                                        boot2/${RP2040_BOOT2}
                                        bootrom/bootrom.c
                                        floating_point/floating_point.c
                                        clocks/clocks.c
                                        int_divider/int_divider.c
                                        memory/memory.c
                                        resets/resets.c
                                        pll/pll.c
                                        xosc/xosc.c
                                        stdlib/assert.c)

target_include_directories(microjava_mal_mcu PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(microjava_mal_mcu PRIVATE -mcpu=${MICROJAVA_COMPILER_CPU})

target_link_libraries(microjava_mal_mcu microjava_shared)