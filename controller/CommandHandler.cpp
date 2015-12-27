//
// Created by ronald on 24-12-15.
//

#include "CommandHandler.h"
#include "../lib/ClientCommand.h"

using namespace std;

CommandHandler::CommandHandler(shared_ptr<GameController> gameController) : gameController(gameController) {
  //  gameController = shared_ptr<GameController>(new GameController);
}

void CommandHandler::handleCommand(ClientCommand command){
    shared_ptr<Socket> client {command.get_client()};
    shared_ptr<Player> player {command.get_player()};
    if(player->isHasTurn()){
        if(gameController->isIsInSetup()){
            handleCommandSetup(command);
        }else{
            handleCommandInGame(command);
        }
    }else{
        client->write("It's not your turn yet!");
    }
}

void CommandHandler::handleCommandSetup(ClientCommand command){
    shared_ptr<Socket> client {command.get_client()};
    shared_ptr<Player> player {command.get_player()};
    int option;
    try {
        option = stoi(command.get_cmd());
        if(gameController->isFirstCard()){
            gameController->pickCard(option, player);
        }else{
            gameController->removeCard(option, player);
        }
    } catch (exception e) {
        client->write("Not a valid option \r\n");
    }
}

void CommandHandler::handleCommandInGame(ClientCommand command){
    shared_ptr<Socket> client {command.get_client()};
    shared_ptr<Player> player {command.get_player()};

    int option;
    try{
        option = stoi(command.get_cmd());
            switch(option){
                case 0 :
                    gameController->getOpponentDetails(player);
                    break;
                case 1 :
                    gameController->addCoins(player, 2);
                    gameController->goToNextPlayerInGame();
              //      gameController->getNextCharacterCard();
                    //g->goToNextCard();
                    break;
                case 2 :
                    gameController->getTwoBuildingCardsAndPutOneBack(player);
                    gameController->goToNextPlayerInGame();
                    break;
                case 3 :
                    break;
<<<<<<< Updated upstream
                case 4 :
                    gameController->showOverview(player);
=======
                default:
                    client->write("Not a valid option!");
>>>>>>> Stashed changes
                    break;
            }
    }catch (exception e){
        client->write("Not a valid command");
    }
}