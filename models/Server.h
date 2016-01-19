//
// Created by ronald on 10-1-16.
//

#ifndef MACHIAVELLI_SERVER_H
#define MACHIAVELLI_SERVER_H


#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include <utility>
#include <vector>
#include <signal.h>
#include "../lib/Socket.h"
#include "../controller/GameController.h"
#include "../controller/CommandHandler.h"

class Server {

//private:
//    // start command consumer thread
//    std::thread consumer {consume_command};
//
//    // keep client threads here, so we don't need to detach them
//    std::vector<std::thread> handlers;
//
//    // create a server socket
//    ServerSocket server;
//    std::shared_ptr<GameController>g;
//    std::unique_ptr<CommandHandler> commandHandler;
//
//public:
//    Server();
//
//    void consume_command();
//
//    void handle_client(std::shared_ptr<Socket> client);

};


#endif //MACHIAVELLI_SERVER_H
