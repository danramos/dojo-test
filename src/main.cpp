#include <NetworkClient.hpp>
#include <Game.hpp>
#include <vector>
#include <iostream>
#include <InputOutput.hpp>
#include <GameHandler.hpp>

int main(int argc, char** argv)
{
    InputOutput io;
    NetworkClient client(std::string(argv[1]), atoi(argv[2]));
    GameHandler handler(io, client);
    handler.play();
}
