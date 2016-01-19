//
// Created by ronald on 24-12-15.
//

#include "CommandHandler.h"
#include "../lib/ClientCommand.h"

using namespace std;

CommandHandler::CommandHandler(shared_ptr<GameController> gameController) : gameController(gameController) {}

void CommandHandler::handleCommand(ClientCommand command){
    shared_ptr<Socket> client {command.get_client()};
    shared_ptr<Player> player {command.get_player()};

    if(player->isHasTurn()){
        if(gameController->isIsInSetup()){
            handleCommandSetup(command);
        }else if(gameController->isIsPlaying() && gameController->isCanBuild()){
            handleCommandToBuild(command);
        }else if(gameController->isLastCommand()){
            handleLastCommand(command);
        }else{
            handleCommandInGame(command);
        }
    }else{
        client->write("It's not your turn yet!\n");
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
        client->write("Not a valid option \r\n machiavli>");
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
                    gameController->showPossibleBuildings(player);
                    player->setChoseMainOption(true);
                    break;
                case 2 :
                    gameController->getTwoBuildingCardsAndPutOneBack(player);
                    gameController->showPossibleBuildings(player);
                    player->setChoseMainOption(true);
                    break;
                case 3 :
                    if(!player->isUsedAbility()) {
                        player->getCharacter()->doSpecialAbility(player, command.get_cmd(), gameController);
                        player->setUsedAbility(true);
                    } else {
                        client->write("Already used your special ability.\n");
                    }
                    break;
                case 4 :
                    gameController->showOverview(player);
                    break;
                default:
                    client->write("Not a valid option!\n");
                    break;
            }
    }catch (exception e){
        client->write("Not a valid command\n");
    }
}

void CommandHandler::handleCommandToBuild(ClientCommand command){
    shared_ptr<Socket> client {command.get_client()};
    shared_ptr<Player> player {command.get_player()};

    int option;

    try{
        option = stoi(command.get_cmd());
        gameController->buildBuilding(option, command.get_player());
    }catch (exception e){
        client->write("Not a valid command\n");
    }
}

void CommandHandler::handleLastCommand(ClientCommand command) {

    shared_ptr<Socket> client{command.get_client()};
    shared_ptr<Player> player{command.get_player()};

    int option;
    try {
        option = stoi(command.get_cmd());
        if(option == 3){
            handleCommandInGame(command);
        }else{
            gameController->getNextCharacterCard();
        }
        gameController->setLastCommand(false);
    }catch(exception e){
        client->write("Not a valid command\n");
    }
}