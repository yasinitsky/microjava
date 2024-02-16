cmake_minimum_required(VERSION 3.12)

add_library(microjava_mal_mcu OBJECT McuMock.cpp)
target_link_libraries(microjava_mal_mcu gmock_main)