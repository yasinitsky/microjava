cmake_minimum_required(VERSION 3.12)

add_library(microjava_test OBJECT DummyTest.cpp)

# compile and link googletest and googlemock
set(INSTALL_GTEST OFF CACHE BOOL "OFF" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty/googletest gmock_bin)
target_link_libraries(microjava_test gmock_main)