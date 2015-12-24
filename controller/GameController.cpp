//
// Created by ronald on 16-12-15.
//
#include <iostream>
#include <sstream>
#include <random>
#include <memory>
#include <algorithm>
#include <fstream>
#include <unistd.h>
#include "GameController.h"
#include "../models/CharacterCardFactory.h"

using namespace std;

void GameController::init() {
    players[0]->setGoldCoins(2);
    players[0]->setIsKing(true);
    players[1]->setGoldCoins(2);

    firstCard = true;
    secondCard = false;

    // Clear all cards incase game restarted
    buildingColors.clear();
    buildingCards.clear();
    characterCards.clear();

    buildingColors.push_back(BuildingColor::YELLOW);
    buildingColors.push_back(BuildingColor::GREEN);
    buildingColors.push_back(BuildingColor::RED);
    buildingColors.push_back(BuildingColor::GREEN);
    buildingColors.push_back(BuildingColor::LILA);
    initBuildingCards();
    initCharacterCards();
    //playRandomCards();
    //setUpRound();
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
    const string pathToBuildingCards {"rescources/Bouwkaarten.csv"};

    //getNextLineAndSplitIntoTokens(pathToBuildingCards);

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
    const string pathToCharacterCards {"rescources/karakterkaarten.csv"};

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

    nextCharacterCard = 0;
    for(shared_ptr<Socket> client : sockets){
        client->write("Starting turn!\r\n");
    }

    for(shared_ptr<Player> player : players){
        player->getCharacterCards().clear();
    }

    shuffle(characterCards.begin(), characterCards.end(), dre);
    shuffle(buildingCards.begin(), buildingCards.end(), dre);

    setUpRound();

    setNextKing();

//    for(shared_ptr<CharacterCard> cc : characterCards){
//        for(shared_ptr<Player> player : players){
//            if(find(player->getCharacterCards().begin(), player->getCharacterCards().end(), cc) != player->getCharacterCards().end()){
//                doPlayerTurn(player, cc);
//            }
//        }
//    }
}

void GameController::doTurn(){
    for(shared_ptr<Socket> client : sockets){
        client->clear_screen();
        client->write("Starting turn!\r\n");
        client->write("Calling characters now...\r\n");
    }

    if(nextCharacterCard < 8) {
        getNextCharacterCard();
    }else{
        doNextTurn();
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
            p->getClient()->write("  -> " + bc->getName() + "  is worth: " + to_string(bc->getValue()) + "\r\n");
        }
    }else{
        p->getClient()->write("  No buildings yet.\r\n");
    }
}

void GameController::showGameUI(shared_ptr<Player> p, shared_ptr<CharacterCard> cc){
    p->getClient()->clear_screen();
    p->getClient()->write("You are now the: " + cc->getName() + "\r\n");
    p->getClient()->write("Gold coins: " + to_string(p->getGoldCoins()) + "\r\n");
    p->getClient()->write("Build buildings: \r\n");
    if(p->getBuildBuildings().size() > 0) {
        for (shared_ptr<BuildingCard> bc : p->getBuildBuildings()) {
            p->getClient()->write("  -> " + bc->getName() + "  is worth: " + to_string(bc->getValue()) + "\r\n");
        }
    }else{
        p->getClient()->write("  No buildings yet.\r\n");
    }

    p->getClient()->write("Cards in hand: \r\n");
    if(p->getBuildingCards().size() > 0) {
        for (shared_ptr<BuildingCard> b : p->getBuildingCards()) {
            p->getClient()->write(
                    "  -> " + b->getName() + " <" + to_string(b->getValue()) + ", " + b->getColorName() + ">\r\n");
        }
    }else{
        p->getClient()->write("  No cards in hand.\r\n");
    }

    p->getClient()->write("Choose an option: \r\n");
    p->getClient()->write("[0] Look at the amount of gold and the buildings of the opponent first.\r\n");
    p->getClient()->write("[1] Take two gold coins.\r\n");
    p->getClient()->write("[2] Take two building cards and put one back.\r\n");
    p->getClient()->write("[3] Use your special abbility: .\r\n");
    p->getClient()->write("[4] Show help.\r\n");
    p->getClient()->write("machiavelli> ");
}

void GameController::setUpRound(){
    isInSetup = true;
    availableCards = characterCards;
    shared_ptr<Player> king;
    shared_ptr<Player> otherPlayer;
    shared_ptr<Player> currentPlayer;

    for(shared_ptr<Player> p : players){
        if(p->isIsKing()){
            king = p;
            currentPlayer = king;
        }else{
            otherPlayer = p;
        }
    }
    king->setHasTurn(true);
    currentPlayer->getClient()->clear_screen();
    currentPlayer->getClient()->write("The top card is: " + availableCards[0]->getName() + "\r\n");
    //currentPlayer->getClient()->write("You put the card on the table and ");
    availableCards.erase(availableCards.begin());
    sleep(3);
    pickOneCardToKeep(currentPlayer);
}

void GameController::pickCard(int index, shared_ptr<Player> player){
    if(index < availableCards.size() && index > -1) {
        player->getCharacterCards().push_back(availableCards[index]);
        availableCards.erase(availableCards.begin() + index);
        if(availableCards.size() == 6){
            goToNextPlayerInSetup();
        }else {
            pickOneCardToRemove(player);
            setFirstCard(false);
            setSecondCard(true);
        }
    }else{
        player->getClient()->write("Not a valid card!\r\n");
        sleep(2);
        pickOneCardToKeep(player);
    }
}

void GameController::removeCard(int index, shared_ptr<Player> player){
    if(index < availableCards.size() && index > -1) {
        availableCards.erase(availableCards.begin() + index);
        goToNextPlayerInSetup();
        if(availableCards.empty()){
            setIsInSetup(false);
            setIsPlaying(true);
            setFirstTurn(true);
            playRandomCards();
            doTurn();
        }
    }else{
        player->getClient()->write("Not a valid card!\r\n");
        sleep(2);
        pickOneCardToRemove(player);
    }
}

void GameController::pickOneCardToKeep(shared_ptr<Player> currentPlayer){
    currentPlayer->getClient()->clear_screen();
    currentPlayer->getClient()->write("Choose one of the cards below to keep: \r\n");
    showAvailableCards(currentPlayer);
}

void GameController::pickOneCardToRemove(shared_ptr<Player> currentPlayer){
    currentPlayer->getClient()->clear_screen();
    currentPlayer->getClient()->write("Choose one of the cards below to remove: \r\n");
    showAvailableCards(currentPlayer);
}

void GameController::goToNextPlayerInSetup(){
    for(shared_ptr<Player> p : players){
        if(!p->isHasTurn()){
            pickOneCardToKeep(p);
            p->setHasTurn(true);
        }else{
            p->getClient()->write("Please wait...\r\n");
            p->setHasTurn(false);
        }
    }
    setFirstCard(true);
    setSecondCard(false);
}

void GameController::goToNextPlayerInGame(){
    for(shared_ptr<Player> p : players){
        if(!p->isHasTurn()){
            p->setHasTurn(true);
        }else{
            p->getClient()->write("Please wait...\r\n");
            p->setHasTurn(false);
        }
    }
}

void GameController::showAvailableCards(std::shared_ptr<Player> currentPlayer) {
    for (int i = 0; i < availableCards.size(); ++i) {
        currentPlayer->getClient()->write("[" + to_string(i) + "] " + availableCards[i]->getName() + "\r\n");
    }
    currentPlayer->getClient()->write("machiavelli> ");
}

void GameController::calculatePoints(shared_ptr<Player> p){
    vector<BuildingColor> colors = buildingColors;
    int points = 0;
    for(shared_ptr<BuildingCard> bb : p->getBuildBuildings()){
        points += bb->getValue();

        for(BuildingColor color : colors){
            if(bb->getColor() == color){
                colors.erase(remove(colors.begin(), colors.end(), color), colors.end());
            }
        }
    }

    if(p->getBuildBuildings().size() >= 8){
        points += 2;
    }

    if(colors.empty()){
        points += 3;
    }

    if(p->isFirstToFinish()){
        points += 4;
    }

    p->setPoints(points);
}

void GameController::addCoins(shared_ptr<Player> p, int amount){
 //   if((goldCoins -= amount) <= 0) {            //Is there game limit of 30 in game coins???
        setGoldCoins(goldCoins -= amount);
        p->setGoldCoins(amount);
  //  }

}

void GameController::getTwoBuildingCardsAndPutOneBack(shared_ptr<Player> p){
    vector<shared_ptr<BuildingCard>> cardsToGet(buildingCards.end() - 2, buildingCards.end());
    buildingCards.erase(buildingCards.end() - 2, buildingCards.end());

    p->getClient()->clear_screen();
    //for
}

void GameController::getNextCharacterCard(){

    if(nextCharacterCard < 7) {
        shared_ptr<CharacterCard> cc = characterCards[nextCharacterCard];

        for (shared_ptr<Player> p : players) {
            if (find(p->getCharacterCards().begin(), p->getCharacterCards().end(), cc) !=
                p->getCharacterCards().end()) {
                if (isFirstTurn()) {
                    p->setHasTurn(true);
                    setFirstTurn(false);
                } else {
                    goToNextPlayerInGame();
                }
                doPlayerTurn(p, cc);
                nextCharacterCard++;
            } else {
                nextCharacterCard++;
                getNextCharacterCard();
            }
            break;
        }
    }
}

void GameController::removePlayer(std::shared_ptr<Player> player) {
    sockets.erase(find(sockets.begin(), sockets.end(), player->getClient()));
    players.erase(find(players.begin(), players.end(), player));
}
