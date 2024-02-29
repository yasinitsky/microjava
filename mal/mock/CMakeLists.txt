cmake_minimum_required(VERSION 3.24)

add_library(microjava_mal_mcu OBJECT src/McuMock.cpp)

target_link_libraries(microjava_mal_mcu microjava_mal_interface gmock)