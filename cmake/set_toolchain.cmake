# this file should be included before project(...)

cmake_minimum_required(VERSION 3.12)

# use this to disable compiler check, because it would fail with cross toolchain
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# By now, only GNU binutils toolchain supported
function(set_toolchain toolchain_prefix)
    find_program(MICROJAVA_ASM_COMPILER ${toolchain_prefix}-gcc)
    if(${MICROJAVA_ASM_COMPILER} STREQUAL "MICROJAVA_ASM_COMPILER-NOTFOUND")
        message(FATAL_ERROR "Could not find assembly ${toolchain_prefix}-gcc")
    endif()

    find_program(MICROJAVA_C_COMPILER ${toolchain_prefix}-gcc)
    if(${MICROJAVA_C_COMPILER} STREQUAL "MICROJAVA_C_COMPILER-NOTFOUND")
        message(FATAL_ERROR "Could not find C compiler ${toolchain_prefix}-gcc")
    endif()

    find_program(MICROJAVA_LINKER ${toolchain_prefix}-ld)
    if(${MICROJAVA_LINKER} STREQUAL "MICROJAVA_LINKER-NOTFOUND")
        message(FATAL_ERROR "Could not find linker ${toolchain_prefix}-ld")
    endif()

    set(CMAKE_ASM_COMPILER ${MICROJAVA_ASM_COMPILER} CACHE FILEPATH "")
    set(CMAKE_C_COMPILER ${MICROJAVA_C_COMPILER} CACHE FILEPATH "")
    set(CMAKE_LINKER ${MICROJAVA_LINKER} CACHE FILEPATH "")
endfunction()