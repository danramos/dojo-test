#include <NetworkClient.hpp>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <cassert>
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <utility>
#include <mutex>

namespace
{
    void sendMessage(int fd, const std::string& msg)
    {
       ::send(fd, msg.c_str(), msg.length() + 1, 0);
    }

    std::pair<std::string, std::string> interpret(const std::string& msg)
    {
        auto pos = msg.find(" ");
        auto prot = msg.substr(0, pos);
        auto payload = msg.substr(pos + 1);
        return {prot, payload};
    }
}


NetworkClient::NetworkClient(const std::string& ip, int port)
    : _ip(ip), _port(port)
{
}

void NetworkClient::join()
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(_sockfd >= 0);

    hostent* server = gethostbyname(_ip.c_str());
    assert(server != nullptr);

    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    std::memcpy((char*)&serv_addr.sin_addr.s_addr,
                (char*)server->h_addr,
                server->h_length);
    serv_addr.sin_port = ::htons(_port);

    const auto connect_res = connect(_sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));
    assert(connect_res >= 0);

    _listener = std::thread(std::bind(&NetworkClient::handle, this));
}


void NetworkClient::leave()
{
    _listener.join();
    ::close(_sockfd);
}

int NetworkClient::findMatch()
{
    _future_player_number = promised_player_number.get_future();
    assert(_future_player_number.valid() == true);
    join();
    _future_player_number.wait();
    auto result = _future_player_number.get();
    return result;
}

bool NetworkClient::notifyMove(int move)
{
    auto message = std::string("move ") + std::to_string(move);
//    std::cout << "sent move notification: " << message << std::endl;
    sendMessage(_sockfd, message );
}

int NetworkClient::getOpponentMove()
{
    auto future_move = promised_opponent_move.get_future();
    future_move.wait();
    auto result =  future_move.get();
    promised_opponent_move = std::promise<int>();
    return result;
}

void NetworkClient::handle()
{
    assert(_sockfd >= 0);
//    std::cout << "ready to receive messages" << std::endl;

    char buffer[256] = {0};
    while(recv(_sockfd, buffer, 255, 0) >=0 )
    {
        auto pack = interpret(std::string(buffer));
//        std::cout << "received: [" << pack.first << "] " << pack.second  << std::endl;

        if (pack.first == "assign")
        {
            int assign = std::stoi(pack.second);
            if (assign != -1) {
                promised_player_number.set_value(assign);
            }
        }
        else if (pack.first == "move")
        {
//            std::cout << "received shit" << pack.second << std::endl;
            promised_opponent_move.set_value(std::stoi(pack.second));
        }
    }
}


