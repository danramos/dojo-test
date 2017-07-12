#pragma once
#include <string>
#include <thread>
#include <condition_variable>
#include <future>
#include <NetworkInterface.hpp>

class NetworkClient : public NetworkInterface
{
public:
   NetworkClient(const std::string& ip, int port);

   void join();

   void leave();

   int findMatch();

   bool notifyMove(int move);

   int getOpponentMove();



private:
   void handle();

   int _sockfd = -1;
    std::string _ip;
    int _port = -1;
    std::thread _listener;

    int player_number = 0;
    std::condition_variable match_ready;
    std::promise<int> promised_player_number;
    std::future<int> _future_player_number;

    std::promise<int> promised_opponent_move;
};
