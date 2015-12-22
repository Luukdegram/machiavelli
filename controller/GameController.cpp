//
// Created by ronald on 16-12-15.
//
#include <iostream>
#include <sstream>
#include <random>
#include <memory>
#include <algorithm>
#include <fstream>
#include "GameController.h"
#include "../models/CharacterCardFactory.h"

using namespace std;

void GameController::init() {
    players[0]->setGoldCoins(2);
    players[0]->setIsKing(true);
    players[1]->setGoldCoins(2);

    initBuildingCards();
    initCharacterCards();
    playRandomCards();
    doNextTurn();
}

void GameController::readCardsFromFile() {

}

vector<vector<string>> GameController::getNextLineAndSplitIntoTokens(const string pathToFile) {

    ifstream str {pathToFile};

    vector<vector<string>> result;
    string line;
    string cell;

    while (getline(str, line))
    {
        stringstream  lineStream(line);
        istringstream iss(line);

        vector<string> lineData {};

        while(std::getline(lineStream,cell,';'))
        {
            if(cell != "\r") {
                lineData.push_back(cell);
            }
        }

        result.push_back(lineData);
    }

    return result;
}

void GameController::initBuildingCards(){
    const string pathToBuildingCards {"/home/ronald/Documents/School/EIndopdrachtc++2/rescources/Bouwkaarten.csv"};

    getNextLineAndSplitIntoTokens(pathToBuildingCards);

    for(vector<string> line : getNextLineAndSplitIntoTokens(pathToBuildingCards)){
        if(line.size() < 4) {
            buildingCards.push_back(shared_ptr<BuildingCard>(new BuildingCard(line[2], line[0], stoi(line[1]))));
        }else{
            buildingCards.push_back(shared_ptr<BuildingCard>(new BuildingCard(line[2], line[0], stoi(line[1]), line[3])));
        }
    }

    shuffle(buildingCards.begin(), buildingCards.end(), dre);
}

void GameController::initCharacterCards(){
    const string pathToCharacterCards {"/home/ronald/Documents/School/EIndopdrachtc++2/rescources/karakterkaarten.csv"};

    for(vector<string> line : getNextLineAndSplitIntoTokens(pathToCharacterCards)){
       // characterCards.push_back(shared_ptr<CharacterCard>(new CharacterCard(stoi(line[0]), line[1])));
        line[1].erase(line[1].size() - 1);
        characterCards.push_back(CharacterCardFactory::getInstance()->createCharacterCard(line[1], line[0]));
    }

    shuffle(characterCards.begin(), characterCards.end(), dre);
}

void GameController::getRandomCharacterCard(shared_ptr<Player> player){
    nextCharacterCard++;
    player->getCharacterCards().push_back(characterCards[nextCharacterCard++]);
}

shared_ptr<BuildingCard> GameController::getRandomBuildingCard(){
    return buildingCards[nextBuildingCard++];
}

void GameController::playRandomCards(){
    playRandomCharacterCards();
    playRandomBuildingCards();

    for(shared_ptr<Socket> client : sockets){
        client->write("Starting game!\r\n");
    }

    for(shared_ptr<Player> p : players) {
        showUI(p);
    }
}

//TODO remove magic numbers
void GameController::playRandomCharacterCards(){
    //Give each player two character cards
    while(nextCharacterCard != 8){
        for (int j = 0; j < 2; ++j) {
            getRandomCharacterCard(players[j]);
        }
    }
}

//TODO remove magic numbers
void GameController::playRandomBuildingCards(){
    //Give each player four building cards
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            players[i]->getBuildingCards().push_back(buildingCards[nextBuildingCard++]);
        }
    }
}

void GameController::doNextTurn(){

    for(shared_ptr<Socket> client : sockets){
        client->write("Starting next turn!\r\n");
    }

    for(shared_ptr<Player> p : players){
        showUI(p);
    }

    nextBuildingCard = 0;
    nextCharacterCard = 0;

    for(shared_ptr<Player> player : players){
        player->getBuildingCards().clear();
        player->getCharacterCards().clear();
    }

    shuffle(characterCards.begin(), characterCards.end(), dre);
    shuffle(buildingCards.begin(), buildingCards.end(), dre);

    playRandomCharacterCards();

    setNextKing();

    for(shared_ptr<CharacterCard> cc : characterCards){
        for(shared_ptr<Player> player : players){
            if(find(player->getCharacterCards().begin(), player->getCharacterCards().end(), cc) != player->getCharacterCards().end()){
                doPlayerTurn(player, cc);
            }
        }
    }
}

void GameController::doPlayerTurn(shared_ptr<Player> player, shared_ptr<CharacterCard> cc){
    //Do stuff so the player can do his turn
    showGameUI(player, cc);
}

void GameController::setNextKing() {
    for (shared_ptr<Player> player : players) {
        for(shared_ptr<CharacterCard> cc : player->getCharacterCards()){
            if(cc->getCharacterType() == CharacterType::KING) {
                for (shared_ptr<Player> p : players) {
                    p->setIsKing(false);
                }
                player->setIsKing(true);
                return;
            }
        }
    }
}

void GameController::showUI(shared_ptr<Player> p){
    p->getClient()->clear_screen();
    p->getClient()->write("Gold coins: " + to_string(p->getGoldCoins()) + "\r\n");
    p->getClient()->write("Build buildings: \r\n");
    if(p->getBuildBuildings().size() > 0) {
        for (shared_ptr<BuildingCard> bc : p->getBuildBuildings()) {
            p->getClient()->write("-> " + bc->getName() + "  is worth: " + to_string(bc->getValue()) + "\r\n");
        }
    }else{
        p->getClient()->write("No buildings yet.\r\n");
    }
}

void GameController::showGameUI(shared_ptr<Player> p, shared_ptr<CharacterCard> cc){
    p->getClient()->clear_screen();
    p->getClient()->write("You are now the: " + cc->getName() + "\r\n");
    p->getClient()->write("Gold coins: " + to_string(p->getGoldCoins()) + "\r\n");
    p->getClient()->write("Build buildings: \r\n");
    if(p->getBuildBuildings().size() > 0) {
        for (shared_ptr<BuildingCard> bc : p->getBuildBuildings()) {
            p->getClient()->write("-> " + bc->getName() + "  is worth: " + to_string(bc->getValue()) + "\r\n");
        }
    }else{
        p->getClient()->write("No buildings yet.\r\n");
    }

    p->getClient()->write("Cards in hand: \r\n");
    for(shared_ptr<BuildingCard> b : p->getBuildingCards()){
        p->getClient()->write("-> " + b->getName() + " <" + to_string(b->getValue()) + ", " + b->getColorName() + ">\r\n");
    }
}
