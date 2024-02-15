include(${CMAKE_SOURCE_DIR}/cmake/set_toolchain.cmake)
set_toolchain("arm-none-eabi")

set(MICROJAVA_LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/default.ld)
set(MICROJAVA_COMPILER_CPU cortex-m0plus)