cmake_minimum_required(VERSION 2.8)
project(self-tests)

set(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror -Wno-return-type")
include_directories("../include")
add_subdirectory(".." TOOLS)

add_executable(${PROJECT_NAME} "test.cpp")
target_link_libraries(${PROJECT_NAME} test-tools)
