cmake_minimum_required(VERSION 2.8)
project(tools)

set(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror -Wno-return-type")
include_directories("./include")
add_library(test-tools SHARED "./src/dojo-test-tools.cpp")

add_executable(self-tests "./test/test.cpp")
target_link_libraries(self-tests test-tools)
