cmake_minimum_required(VERSION 3.12)

add_library(mcu OBJECT McuMock.cpp)
target_link_libraries(mcu gmock_main)