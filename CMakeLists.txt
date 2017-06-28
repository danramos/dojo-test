cmake_minimum_required(VERSION 2.8)

project(dojo-bare-test)

set(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror -Wno-return-type")

add_subdirectory("tools")

include_directories("./include" "./tools/include")

add_executable(${PROJECT_NAME} "test/test.cpp")

target_link_libraries(${PROJECT_NAME} test-tools)
