#pragma once
#include <vector>
#include <InputOutputInterface.hpp>

class InputOutput :  public InputOutputInterface
{
public:

    void displayWelcome(int player);

    void display(int player, const std::vector<std::vector<int>>& layout);

    void displayWinner(int player);

    int prompt();

};

