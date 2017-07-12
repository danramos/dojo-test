#include <InputOutput.hpp>
#include <string>
#include <iostream>

void InputOutput::display(int player, const std::vector<std::vector<int> >& layout)
{
    if (player == 0) {
        std::cout << "\n Waiting for opponent move." << std::endl;
    } else {
        std::cout << "\n     Player " << player << "'s turn.\n";
    }
    std::cout << "    ._______________." <<std::endl;
    for (const auto& row : layout) {
        std::cout << "    | ";
        for (const auto& col : row) {
            if (col == 0)
                std::cout << ". ";
            else
                std::cout << col << " ";
        }
        std::cout << "| ";
        std::cout << std::endl;
    }
    std::cout << "    -----------------" <<std::endl;
    std::cout << "      0 1 2 3 4 5 6 \n" << std::endl;
}

void InputOutput::displayWinner(int player)
{
    std::cout << "****  WINNER: Player "  << player << "  ****" <<std::endl;
}

int InputOutput::prompt()
{
    int x;
    std::cout << "Enter column(0-6): ";
    std::cin >> x;
    return x;
}

void InputOutput::displayWelcome(int player)
{
   std::cout << "Welcome player "<< player << "!" << std::endl;
}
