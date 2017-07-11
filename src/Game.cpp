#include <Game.hpp>

Game::BoardType Game::getLayout() const
{
    return _board;
}

Game::Game()
{
    _board.resize(6);
    for (auto& row : _board) {
        row.resize(7);
    }
}

void Game::place(int player, int column)
{

}
