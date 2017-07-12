#include <GameHandler.hpp>
#include <iostream>


GameHandler::GameHandler(InputOutputInterface& io, NetworkInterface& client) :
    io(io), client(client)
{

}

void GameHandler::play()
{
    bool first_turn = true;
    int player_number = client.findMatch();
    int opponent = player_number == 1 ? 2 : 1;
    io.displayWelcome(player_number);

    try {
        while (true)
        {
            io.display(1, game.getLayout());

            if (!first_turn || (first_turn && player_number == 1)) {
                int move = 0;
                do {
                    move = io.prompt();
                } while (!game.isAdditionalTokenAllowed(move));

                game.place(player_number, move);
                io.display(0, game.getLayout());
                client.notifyMove(move);


                auto check_win = game.getWinner();
                if (check_win != 0) {
                    io.displayWinner(check_win);
                    break;
                }
            }

            std::cout << "...." << std::endl;
            int opponent_move = client.getOpponentMove();
            game.place(opponent, opponent_move);

            auto check_win_2 = game.getWinner();
            if (check_win_2 != 0) {
                io.displayWinner(check_win_2);
                break;
            }

            first_turn = false;
        }
    }
    catch(...) {
        client.leave();
    }

    client.leave();
}
