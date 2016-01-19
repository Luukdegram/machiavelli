//
//  main.cpp
//  socketexample
//
//  Created by Bob Polis on 16/09/14.
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include <utility>
#include <vector>
#include <bits/signum.h>
#include <signal.h>

using namespace std;

#include "lib/Socket.h"
#include "lib/Sync_queue.h"
#include "lib/ClientCommand.h"
#include "models/Player.hpp"
#include "controller/GameController.h"
#include "controller/CommandHandler.h"

namespace machiavelli {
    const int tcp_port {1080};
    const string prompt {"machiavelli> "};
}

//TODO put the server stuff in a seperate class
shared_ptr<GameController>g(new GameController);
unique_ptr<CommandHandler> commandHandler(new CommandHandler(g));
static Sync_queue<ClientCommand> queue;

void consume_command() // runs in its own thread
{
    try {
        while (true) {
			ClientCommand command {queue.get()}; // will block here unless there are still command objects in the queue
			shared_ptr<Socket> client {command.get_client()};
			shared_ptr<Player> player {command.get_player()};

			try {
                commandHandler->handleCommand(command);
				//*client << player->get_name() << ", you wrote: '" << command.get_cmd() << "', but I'll ignore that for now.\r\n" << machiavelli::prompt;
			} catch (const exception& ex) {
				cerr << "*** exception in consumer thread for player " << player->get_name() << ": " << ex.what() << '\n';

                client->close();

				if (client->is_open()) {
					client->write("Sorry, something went wrong during handling of your request.\r\n");
				}
            } catch (...) {
				cerr << "*** exception in consumer thread for player " << player->get_name() << '\n';
				if (client->is_open()) {
					client->write("Sorry, something went wrong during handling of your request.\r\n");
				}
			}
        }
    } catch (...) {
        cerr << "consume_command crashed, restarting... \n";
        consume_command();
    }
}

void handle_client(shared_ptr<Socket> client) // this function runs in a separate thread
{
    try {
        client->write("Welcome to Server 1.0! To quit, type 'quit'.\r\n");
		client->write("What's your name?\r\n");
        client->write(machiavelli::prompt);
		string name {client->readline()};
		shared_ptr<Player> player {new Player {name, client}};
        g->getPlayers().push_back(player);
		*client << "Welcome, " << name << ", have fun playing our game!\r\n" << machiavelli::prompt;
        g->getSockets().push_back(client);
        //Initialize the game when there are enough players

        if(g->getPlayers().size() == 2){
            g->init();
        }

        while (true) { // game loop
            try {
                if(client->is_open()) {
                    // read first line of request
                    string cmd{client->readline()};
                    cerr << '[' << client->get_dotted_ip() << " (" << client->get_socket() << ") " << player->get_name() << "] " << cmd << '\n';

                    if (cmd == "quit") {
                        client->write("Bye!\r\n");
                        break;
                    }

                    if(!player->isBlocked()) {
                        ClientCommand command{cmd, client, player};
                        queue.put(command);
                    } else {
                        queue.clear();
                    }
                } else {
                    break;
                }

            } catch (const exception& ex) {
				cerr << "*** exception in client handler thread for player " << player->get_name() << ": " << ex.what() << '\n';
				if (client->is_open()) {
					*client << "ERROR: " << ex.what() << "\r\n";
				}
            } catch (...) {
				cerr << "*** exception in client handler thread for player " << player->get_name() << '\n';
				if (client->is_open()) {
					client->write("ERROR: something went wrong during handling of your request. Sorry!\r\n");
				}
            }
        }
		if (client->is_open()) {
            client->close();

            string name = player->get_name();
            g->removePlayer(player);

            for(shared_ptr<Player> player : g->getPlayers()) {
                *player->getClient() << name << " has left the game. Please wait for a new player to join. \n";
                *player->getClient() << machiavelli::prompt;
            }
        }
	} catch (...) {
        cerr << "handle_client crashed\n";
    }
}

int main(int argc, const char * argv[])
{
    signal(SIGPIPE, SIG_IGN);

    // start command consumer thread
    thread consumer {consume_command};

    // keep client threads here, so we don't need to detach them
    vector<thread> handlers;

	// create a server socket
	ServerSocket server {machiavelli::tcp_port};

    while (true) {
		try {
			while (true) {
				// wait for connection from client; will create new socket
				cerr << "server listening" << '\n';
				unique_ptr<Socket> client {server.accept()};

				// communicate with client over new socket in separate thread
                thread handler {handle_client, move(client)};
				handlers.push_back(move(handler));
			}
		} catch (const exception& ex) {
			cerr << ex.what() << ", resuming..." << '\n';
        } catch (...) {
            cerr << "problems, problems, but: keep calm and carry on!\n";
        }
	}
    return 0;
}

