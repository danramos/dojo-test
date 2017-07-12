#pragma once

class InputOutputInterface
{
public:
    virtual void displayWelcome(int player) = 0;

    virtual void display(int player, const std::vector<std::vector<int>>& layout) = 0;

    virtual void displayWinner(int player) = 0;

    virtual int prompt() = 0;

};


