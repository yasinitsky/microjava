cmake_minimum_required(VERSION 3.24)

add_library(microjava_mal_mcu STATIC mcu_main.c main.S)

add_subdirectory(${CMAKE_SOURCE_DIR}/drivers/mcu/rp2040 rp2040_driver_bin)
target_link_libraries(microjava_mal_mcu PUBLIC microjava_shared "$<LINK_LIBRARY:WHOLE_ARCHIVE,microjava_rp2040_driver>")