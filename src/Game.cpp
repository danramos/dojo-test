#include <Game.hpp>
#include <iostream>

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
    for (auto i = 5; i >= 0; i--)
    {
        if (_board[i][column] == 0) {
            _board[i][column] = player;
            break;
        }
    }
}

bool Game::isAdditionalTokenAllowed(int column) const
{

    return column >= 0 && column <= 6 && 0 == _board[0][column];
}


int Game::getWinner() const
{
   //vertical?
   //first column
    for (auto column = 0; column < 7; column++) {
       for (auto row = 0; row < 3; row++) {
           if (_board[row][column] != 0
                   && detail::is_four_in_a_line(_board[row][column], _board[row+1][column], _board[row+2][column], _board[row+3][column]))
               return _board[row][column];
       }
   }

   for (auto row = 0; row < 6 ; row++) {
       for (auto column = 0; column < 7 -4 + 1; column++) {
           if (_board[row][column] != 0
                   && detail::is_four_in_a_line(_board[row][column], _board[row][column + 1], _board[row][column +2], _board[row][column + 3]))
               return _board[row][column];
       }
   }


   //diagnoal
   for (auto row = 0; row < 6 - 4 + 1 ; row++) {
       for (auto column = 0; column < 7 -4 + 1; column++) {
           if (_board[row][column] != 0
                   && detail::is_four_in_a_line(_board[row][column], _board[row + 1][column + 1], _board[row+2][column +2], _board[row+3][column + 3]))
               return _board[row][column];
       }
   }

   //negative diagonal
   for (auto row = 5; row > 6 -4 + 1 ; row--) {
       for (auto column = 0; column < 7 - 4 + 1 ; column++) {
           if (_board[row][column] != 0
                   && detail::is_four_in_a_line(_board[row][column], _board[row - 1][column + 1], _board[row - 2][column +2], _board[row - 3][column + 3]))
               return _board[row][column];
       }
   }

   return 0;
}


bool detail::is_four_in_a_line(int a, int b, int c, int d)
{
    return (a == b) && (b == c) && (c == d);
}
