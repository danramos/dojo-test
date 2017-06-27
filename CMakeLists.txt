cmake_minimum_required(VERSION 2.8)
project(dojo-test)

set(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror")

include_directories("./include")
add_executable(dojo-test
               test/test.cpp)


