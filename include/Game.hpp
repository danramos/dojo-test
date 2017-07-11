#pragma once
#include <vector>

class Game
{
public:
    using BoardType = std::vector<std::vector<int>>;

    BoardType getLayout() const;

    Game();

    void place(int player, int column);

private:
    BoardType _board;
};
