cmake_minimum_required(VERSION 2.8)

project(four-in-a-line)

set(PROJECT_TEST "${PROJECT_NAME}-test")

set(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror -Wno-return-type")

add_subdirectory("tools")

include_directories("./include" "./tools/include")
file(GLOB sources "./src/Game.cpp")

add_executable(${PROJECT_TEST} "test/test.cpp" ${sources})
add_executable(game-server "./src/game-server.cpp")
add_executable(${PROJECT_NAME} "./src/Game.cpp"
                                "./src/NetworkClient.cpp"
                                "./src/main.cpp"
                                "./src/InputOutput.cpp"
                                "./src/GameHandler.cpp")
target_link_libraries(${PROJECT_TEST} test-tools)
target_link_libraries(game-server pthread)
target_link_libraries(${PROJECT_NAME} pthread)
