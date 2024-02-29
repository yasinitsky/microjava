cmake_minimum_required(VERSION 3.13)

# use OBJECT because symbols from static will be considered as unused and removed by linker
add_library(microjava_test OBJECT src/DummyTest.cpp)

# compile and link googletest and googlemock
target_link_libraries(microjava_test gtest_main gtest)