cmake_minimum_required(VERSION 2.8)

project(dojo-bare)

set(PROJECT_TEST "${PROJECT_NAME}-test")

set(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror -Wno-return-type")

add_subdirectory("tools")

include_directories("./include" "./tools/include")

add_executable(${PROJECT_TEST} "test/test.cpp")

target_link_libraries(${PROJECT_TEST} test-tools)
