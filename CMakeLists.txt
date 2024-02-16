cmake_minimum_required(VERSION 3.12)

# select MCU by board name
include(cmake/board_mcu_map.cmake)

if(NOT DEFINED MICROJAVA_BOARD)
    message(FATAL_ERROR "MICROJAVA_BOARD is not specified.")
endif()

board_mcu_map_find(MICROJAVA_MCU ${MICROJAVA_BOARD})

if(MICROJAVA_MCU STREQUAL "")
    message(FATAL_ERROR "Incorrent MICROJAVA_BOARD value provided.")
endif()

# load MCU-specific options (toolchain, linker script etc)
include(mal/${MICROJAVA_MCU}/mcu_options.cmake)

project(microjava LANGUAGES ASM C CXX)

string(TOUPPER MJ_BOARD_${MICROJAVA_BOARD} MICROJAVA_BOARD_DEFINE)
string(TOUPPER MJ_MCU_${MICROJAVA_MCU} MICROJAVA_MCU_DEFINE)

add_compile_definitions(${MICROJAVA_MCU_DEFINE} ${MICROJAVA_BOARD_DEFINE})

add_compile_options(-mtune=${MICROJAVA_COMPILER_CPU} ${MICROJAVA_COMPILER_OPTIONS} -Wall)

add_executable(microjava cmake/null.c)

add_subdirectory(mal/interface)
add_subdirectory(mal/${MICROJAVA_MCU})

add_subdirectory(shared)

if(DEFINED MICROJAVA_LINKER_SCRIPT)
    set_target_properties(microjava PROPERTIES LINK_DEPENDS ${MICROJAVA_LINKER_SCRIPT})
    target_link_options(microjava PRIVATE -nostdlib -T ${MICROJAVA_LINKER_SCRIPT})
endif()

target_link_libraries(microjava mcu)

if(MICROJAVA_BOARD STREQUAL "mock")
    add_subdirectory(test)
    target_link_libraries(microjava microjava_test)
endif()