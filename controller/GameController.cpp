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

//TODO make cheat setup for debugging

void GameController::doNextTurn(){
    if(!isLastRound()) {
        nextCharacterCard = 0;
        for (shared_ptr<Socket> client : sockets) {
            client->write("Starting turn!\r\n");
        }

        for (shared_ptr<Player> player : players) {
            player->getCharacterCards().clear();
        }

        shuffle(characterCards.begin(), characterCards.end(), dre);
        shuffle(buildingCards.begin(), buildingCards.end(), dre);

        setUpRound();

        setNextKing();
    }else {
        for (shared_ptr<Player> player : players) {
            calculatePoints(player);
        }
        determineWinner();
    }
}

void GameController::determineWinner(){
    if (players[0]->getPoints() > players[1]->getPoints()) {
        for (shared_ptr<Player> player : players) {
            player->getClient()->write(players[0]->getName() + " won the game with " + to_string(players[0]->getPoints()) + " points! \r\n");
        }
    }else if(players[0]->getPoints() < players[1]->getPoints()){
        for (shared_ptr<Player> player : players) {
            player->getClient()->write(players[1]->getName() + " won the game with " + to_string(players[1]->getPoints()) + " points! \r\n");
        }
    }else {
        for (shared_ptr<Player> player : players) {
            calculatePointsByBuildings(player);
        }

        if(players[0]->getPoints() == players[1]->getPoints()){
            for (shared_ptr<Player> player : players) {
                player->getClient()->write("It's a draw! Both players have " + to_string(players[0]->getPoints()) + " get points!");
            }
        }else{
            determineWinner();
        }
    }
}

void GameController::calculatePointsByBuildings(shared_ptr<Player> player){
    int points = 0;
    for(shared_ptr<BuildingCard> bc : player->getBuildBuildings()){
        points += bc->getValue();
    }

    player->setPoints(points);
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
    p->getClient()->write("[3] Use your special ability: .\r\n");
    p->getClient()->write("[4] Show help.\r\n");
    p->getClient()->write("machiavelli> ");
}

void GameController::setUpRound(){
    isInSetup = true;
    setFirstCard(true);
    setSecondCard(false);
    setCanBuild(false);
    availableCards = characterCards;
    shared_ptr<Player> king;
    shared_ptr<Player> otherPlayer;
    shared_ptr<Player> currentPlayer;

    for(shared_ptr<Player> p : players){
        p->setHasTurn(false);
        if(p->isIsKing()){
            king = p;
            currentPlayer = king;
        }else{
            otherPlayer = p;
        }
    }
    setIsInSetup(true);
    setIsPlaying(false);
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

void GameController::goToNextPlayerInGame(shared_ptr<Player> p){
    for(shared_ptr<Player> player : players){
        if(player == p){
            player->setHasTurn(true);
        }else{
            player->setHasTurn(false);
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
    setGoldCoins(goldCoins -= amount);
    p->setGoldCoins(p->getGoldCoins() + amount);
}

void GameController::getTwoBuildingCardsAndPutOneBack(shared_ptr<Player> p){
    buildingCards.erase(buildingCards.end() - 2, buildingCards.end());
    p->getClient()->clear_screen();
}

void GameController::getNextCharacterCard(){
    setCanBuild(false);
    if(nextCharacterCard <= 7) {
        shared_ptr<CharacterCard> cc = characterCards[nextCharacterCard];

        for (int i = 0; i < players.size(); i++) {
            shared_ptr<Player> p = players[i];
            if (find(p->getCharacterCards().begin(), p->getCharacterCards().end(), cc) !=
                p->getCharacterCards().end()) {
                if (isFirstTurn()) {
                    p->setHasTurn(true);
                    setFirstTurn(false);
                } else {
                    goToNextPlayerInGame(p);
                }
                if(p->isStolen()) {
                    int amount = p->getGoldCoins();
                    getOpponent(p)->setGoldCoins(getOpponent(p)->getGoldCoins() + amount);
                    p->getClient()->write("You have been robbed! \n");
                    p->setStolen(false);
                    sleep(1);
                }
                p->setCharacter(cc);
                if(p->isKilled()){
                    getNextCharacterCard();
                } else {
                    doPlayerTurn(p, cc);
                }
                nextCharacterCard++;
                break;
            }

            if(i == 1){
                nextCharacterCard++;
                getNextCharacterCard();
            }
        }
    }
    else{
        doNextTurn();
    }
}

void GameController::removePlayer(std::shared_ptr<Player> player) {
    sockets.erase(find(sockets.begin(), sockets.end(), player->getClient()));
    players.erase(find(players.begin(), players.end(), player));
}

void GameController::getOpponentDetails(std::shared_ptr<Player> player) {
    shared_ptr<Socket> client = player->getClient();
    for(shared_ptr<Player> current : players) {
        if(current != player) {
            client->write("Player " + current->get_name() + " has: \r\n ");
            client->write(to_string(current->getGoldCoins()) + " coins \r\n");

            if(current->getBuildBuildings().size() > 0) {
                client->write("The player also has the following buildings: \r\n");

                for(shared_ptr<BuildingCard> card : current->getBuildBuildings()) {
                    client->write(card->getName() + "\r\n");
                }
            }
        }
    }
}

void GameController::showOverview(std::shared_ptr<Player> player) {
    shared_ptr<Socket> client = player->getClient();

    client->write("Verloop van het spel: \r\n");
    client->write("Inkomsten: Neem 2 goudstukken of neem 2 kaarten en leg er 1 af. \r\n");
    client->write("Bouwen: Leg één bouwkaart neer en betaal de waarden. \r\n");

    client->write("\r\n Karakter kaarten: \r\n");

    // print all cards
    client->write("Moordenaar: Vermoord een andere karakter. \r\n");
    client->write("Dief: Steelt van een andere speler. \r\n");
    client->write("Magiër: Ruilt bouwkaarten om. \r\n");
    client->write("Koning: Begint de volgende beurt; Ontvangt van monumenten. \r\n");
    client->write("Prediker: Is beschermd tegen de Condottiere; Ontvangt van kerkelijke gebouwen. \r\n");
    client->write("Koopman: Ontvangt één extra goudstuk; Ontvangt van commerciële gebouwen. \r\n");
    client->write("Bouwmeester: Trekt twee extra kaarten; Mag drie gebouwen gebouwen. \r\n");
    client->write("Condottiere: Vernietigt een gebouw; Ontvangt van alle militaire gebouwen. \r\n");
}

std::shared_ptr<Player> GameController::getOpponent(shared_ptr<Player> player) {
    for(shared_ptr<Player> current : players) {
        if (current != player) return current;
    }

    return nullptr;
}

void GameController::showPossibleBuildings(shared_ptr<Player> player){
    setCanBuild(true);
    shared_ptr<Socket> client = player->getClient();

    client->clear_screen();
    client->write("Possible buildings you can build: \r\n");

    for(int i = 0; i < player->getBuildingCards().size(); i++){
        if(player->getBuildingCards()[i]->getValue() <= player->getGoldCoins()) {
            client->write("[" + to_string(i) + "] " + player->getBuildingCards()[i]->getName() + "\r\n");
        }
    }
    client->write("If you don't want to build a building, type '123' \r\n machiavli>");
}

void GameController::buildBuilding(int option, shared_ptr<Player> player){
    shared_ptr<Socket> client = player->getClient();

    if(option == 123){
        getNextCharacterCard();
    }else if(option > -1 && option < player->getBuildingCards().size() && (player->getBuildingCards()[option]->getValue() <= player->getGoldCoins())){
        client->write("You expanded your city with " + player->getBuildingCards()[option]->getName() + "\r\n");
        player->setGoldCoins(player->getGoldCoins() - player->getBuildingCards()[option]->getValue());
        player->getBuildBuildings().push_back(player->getBuildingCards()[option]);
        player->getBuildingCards().erase(player->getBuildingCards().begin() + option);
        if(player->getBuildBuildings().size() >= 8){
            setFirstToFinish(player);
            setLastRound(true);
        }
        getNextCharacterCard();
    }else{
        client->write("Not a valid option! \r\n");
        sleep(1);
        showPossibleBuildings(player);
    }
}

void GameController::setFirstToFinish(shared_ptr<Player> p){
    bool alreadySet = false;
    for (int i = 0; i < players.size(); ++i) {
        if(players[i]->isFirstToFinish()){
            alreadySet = true;
        }
    }

    if(!alreadySet) p->setFirstToFinish(true);
}