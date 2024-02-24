cmake_minimum_required(VERSION 3.12)

add_library(microjava_shared STATIC ${CMAKE_SOURCE_DIR}/cmake/null.c)
target_include_directories(microjava_shared PUBLIC include)