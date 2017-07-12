#include <Game.hpp>
#include <iostream>

Game::BoardType Game::getLayout() const
{
    return {};
}

Game::Game()
{
}

void Game::place(int player, int column)
{
}

bool Game::isAdditionalTokenAllowed(int column) const
{
    return false;
}

int Game::getWinner() const
{
    return -1;
}
