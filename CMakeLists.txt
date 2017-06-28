cmake_minimum_required(VERSION 2.8)
project(rational-numbers)

set(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror -Wno-return-type")

include_directories("./include")
add_executable(${PROJECT_NAME} "src/Rational.cpp" "test/test.cpp" "test/dojo-test-tools.cpp")
