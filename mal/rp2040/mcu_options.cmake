include(${CMAKE_SOURCE_DIR}/cmake/set_toolchain.cmake)
set_toolchain("arm-none-eabi")

set(MICROJAVA_LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/mcu/rp2040/src/default.ld)
set(MICROJAVA_COMPILER_CPU cortex-m0plus)