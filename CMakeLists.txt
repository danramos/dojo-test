cmake_minimum_required(VERSION 2.8)

project(look-and-say)

set(PROJECT_TEST "${PROJECT_NAME}-test")

set(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror -Wno-return-type")

add_subdirectory("tools")

include_directories("./include" "./tools/include")
file(GLOB sources "./src/*.cpp")

add_executable(${PROJECT_TEST} "test/test.cpp" ${sources})

target_link_libraries(${PROJECT_TEST} test-tools)
