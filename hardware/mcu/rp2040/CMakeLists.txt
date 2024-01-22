cmake_minimum_required(VERSION 3.12)

include(${CMAKE_CURRENT_LIST_DIR}/boards.cmake)

microjava_map_find(rp2040_board_boot2 RP2040_BOOT2 ${MICROJAVA_BOARD})
if(RP2040_BOOT2 STREQUAL "")
    message(FATAL_ERROR "Can't find a 2nd stage bootloader that matches board " ${MICROJAVA_BOARD} ".")
endif()

add_library(mcu OBJECT )
target_include_directories(mcu PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(mcu PRIVATE -mcpu=${MICROJAVA_COMPILER_CPU})