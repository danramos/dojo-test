#pragma once
#include <Game.hpp>
#include <InputOutputInterface.hpp>
#include <NetworkInterface.hpp>

class GameHandler
{
    Game game;
    InputOutputInterface& io;
    NetworkInterface& client;

public:
    GameHandler(InputOutputInterface& io, NetworkInterface& client);
    void play();
};

