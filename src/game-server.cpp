#include <iostream>
#include <cassert>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <list>
#include <queue>
#include <signal.h>
#include <functional>

namespace constants
{
    const int LISTEN_PORT = 15007;
}

int waiting_player = -1;
int game_number = 1;

struct GameData
{
    int player1;
    int player2;

    GameData(int a, int b) : player1(a), player2(b) {}

    void forward_message(int from, std::string m)
    {
        if(from == player1)
            send(player2, m.c_str(), m.length() + 1, 0);
        else
            send(player1, m.c_str(), m.length() + 1, 0);
    }
};

    void send_string(int connection, const std::string& message)
    {
        std::cout << "sent to " << connection << ": " << message << std::endl;
        ::send(connection, message.c_str(), message.length() + 1, 0);
    }


void listenForMessages(int socketId, GameData* x)
{
    std::cout << "Listener started for socketId: " << socketId  << std::endl;
    char buffer[256];

    while (recv(socketId,buffer,255, 0) > 0) {
        std::string msg = std::string(buffer);
        x->forward_message(socketId, msg);
    }
    std::cout << "read error/socket closed" << std::endl;
}


void assign_player_number(int sock, int player)
{
     std::string connect_ack = "assign: " + std::to_string(player);
     send(sock, connect_ack.c_str(), connect_ack.length() + 1, 0);
}

class GameInstance
{
public:
   GameInstance(int player1, int player2) : _player1(player1), _player2(player2)
   {
        _ndfs = std::max(_player1, _player2) + 1;
   }

   void startListening()
   {
       std::cout << "GameInstance started listening between: " << _player1 << ", " << _player2 << std::endl;
       _thread = std::thread([this]() { listeningThread(); });
   }

   void listeningThread()
   {
        std::cout << "started listening" << std::endl;

        try {
            std::vector<int> socks = {_player1, _player2};
            while(true) {
                FD_ZERO(&_fds);
                FD_SET(_player1, &_fds);
                FD_SET(_player2, &_fds);

                auto activity = select(_ndfs, &_fds, nullptr, nullptr, nullptr);
                assert(activity >= 0);

                if (FD_ISSET(_player1, &_fds)) {
                    auto message = receiveMessage(_player1);                    ;
                    if (message == "error")
                        throw "shit";

                    std::cout << "Received message from " << _player1 << ": " << message << std::endl;

                    if (message.find("move") != std::string::npos)
                    {
                            send_string(_player2, message);
                    }
                }

                if (FD_ISSET(_player2, &_fds)) {
                    auto message = receiveMessage(_player2);                    ;
                    if (message == "error")
                        throw "shit";

                    std::cout << "Received message from " << _player2 << ": " << message << std::endl;

                    if (message.find("move") != std::string::npos)
                    {
                            send_string(_player1, message);
                    }
                }


            }
        }
        catch(...)
        {
            std::cout << "Issue occurs. exiting thread..." << std::endl;
            close(_player1);
            close(_player2);
        }
   }

   void leave()
   {
       std::cout << "Game isntance closing sockets" << std::endl;
        close(_player1);
        close(_player2);
        _thread.join();
   }

   std::string receiveMessage(int conn)
   {
       char buffer[256];
       if (recv(conn, buffer, 256, 0) <= 0)
       {
          return "error";
       }

       return std::string(buffer);
   }

    int _player1 = -1;
    int _player2 = -1;
    int _ndfs = -1;
    fd_set _fds;
    std::thread _thread;

};

class GameCoordinator
{
public:
    std::vector<GameInstance*> _list;

    GameCoordinator()
    {
    }


    void init(int port)
    {
        _listening_socket = socket(AF_INET, SOCK_STREAM, 0);
        assert(_listening_socket >= 0 && "socket creation failed");

        sockaddr_in serv_addr;
        std::memset((char*)&serv_addr,0 , sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);

        auto res = bind(_listening_socket, (sockaddr*) &serv_addr, sizeof(serv_addr));
        assert(res >= 0 && "Failed binding to local port");

        std::cout << "Game coordinator initialized at local port: " << port << std::endl;
    }

    void listenForConnections()
    {
        assert(_listening_socket >= 0);
        listen(_listening_socket, 30);

        sockaddr_in cli_addr;
        socklen_t clilen;

        while (true) {
            int newsockfd = accept(_listening_socket, (sockaddr*)&cli_addr, &clilen);
            std::cout << "Accepted connection in socket: " << newsockfd <<  std::endl;

            if (waiting_player == -1) {
                sendPlayerAssignment(newsockfd, -1);
                waiting_player = newsockfd;
            } else {
                sendPlayerAssignment(waiting_player, 1);
                sendPlayerAssignment(newsockfd, 2);

                auto x = new GameInstance(waiting_player, newsockfd);
                x->startListening();
                _list.push_back(x);
                waiting_player = -1;
            }
        }
    }

    void sendPlayerAssignment(int connection, int assignment)
    {
        auto message = "assign " + std::to_string(assignment);
        sendMessage(connection, message);
    }

    void sendMessage(int connection, const std::string& message)
    {
        ::send(connection, message.c_str(), message.length() + 1, 0);
    }

    void close()
    {
        std::cout << "Caught signal.. closing all sockets";
        ::close(_listening_socket) ;

        for(auto i : _list) {
            i->leave();
        }
        ::exit(1);
    }

public:

    int game_id = 0;
    int _listening_socket = -1;
    int _waiting_player_id = -1;
};

std::function<void()> handler;
void mySignalHandler(int)
{
   handler();
}
int main()
{
    GameCoordinator coordinator;

    handler = std::bind(&GameCoordinator::close, coordinator);
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = mySignalHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);



    coordinator.init(constants::LISTEN_PORT);
    coordinator.listenForConnections();


    sockaddr_in cli_addr;
    socklen_t clilen;

    while(true) {
        int newsockfd = accept(coordinator._listening_socket, (sockaddr*)&cli_addr, &clilen);
        std::cout << "established " << newsockfd <<  std::endl;

        if (waiting_player == -1) {
            assign_player_number(newsockfd, -1);
            waiting_player = newsockfd;
        } else {
            assign_player_number(waiting_player, 1);
            assign_player_number(newsockfd, 2);

            auto x = new GameData(waiting_player, newsockfd);
            std::thread t1(listenForMessages, waiting_player, x);
            t1.detach();
            std::thread t2(listenForMessages, newsockfd, x);
            t2.detach();
            waiting_player = -1;
        }
    }
}
