cmake_minimum_required(VERSION 3.12)

add_subdirectory(interface)
add_subdirectory(${MICROJAVA_MCU})

add_library(microjava_mal OBJECT ${CMAKE_SOURCE_DIR}/cmake/null.c)

target_link_libraries(microjava_mal microjava_mal_interface microjava_mal_mcu)