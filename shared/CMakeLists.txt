cmake_minimum_required(VERSION 3.24)

add_library(microjava_shared INTERFACE ${CMAKE_SOURCE_DIR}/cmake/null.c)
target_include_directories(microjava_shared INTERFACE include)