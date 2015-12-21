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
    players.push_back(shared_ptr<Player>(new Player("test player 1")));
    players.push_back(shared_ptr<Player>(new Player("test player 2")));
    players[0]->setGoldCoins(2);
    players[0]->setIsKing(true);
    players[1]->setGoldCoins(2);

    initBuildingCards();
    initCharacterCards();
    playRandomCards();
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
    characterCards[nextCharacterCard++];
    player->getCharacterCards().push_back(characterCards[nextCharacterCard++]);
}

shared_ptr<BuildingCard> GameController::getRandomBuildingCard(){
    return buildingCards[nextBuildingCard++];
}

//TODO remove magic numbers
void GameController::playRandomCards(){
    //Give each player two character cards
    while(nextCharacterCard != 8){
        for (int j = 0; j < 2; ++j) {
            getRandomCharacterCard(players[j]);
        }
    }

    //Give each player four building cards
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            players[i]->getBuildingCards().push_back(buildingCards[nextBuildingCard++]);
        }
    }
}

void GameController::doNextTurn(){

    nextBuildingCard = 0;
    nextCharacterCard = 0;

    for(shared_ptr<Player> player : players){
        player->getBuildingCards().clear();
        player->getCharacterCards().clear();
    }

    shuffle(characterCards.begin(), characterCards.end(), dre);
    shuffle(buildingCards.begin(), buildingCards.end(), dre);

    playRandomCards();

    for(shared_ptr<CharacterCard> cc : characterCards){
        for(shared_ptr<Player> player : players){
            if(find(player->getCharacterCards().begin(), player->getCharacterCards().end(), cc) != player->getCharacterCards().end()){
                doPlayerTurn(player);
            }
        }
    }
}

void GameController::doPlayerTurn(shared_ptr<Player> player){
    //Do stuff so the player can do his turn
}

void GameController::setNextKing() {
//    for (shared_ptr<Player> player : players) {
//        for
//    }
}
