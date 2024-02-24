cmake_minimum_required(VERSION 3.12)

add_library(microjava_mal_mcu STATIC mcu_main.c)

add_subdirectory(${CMAKE_SOURCE_DIR}/drivers/mcu/rp2040 rp2040_driver_bin)
target_link_libraries(microjava_mal_mcu microjava_shared microjava_rp2040_driver)