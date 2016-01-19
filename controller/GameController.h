//
// Created by ronald on 16-12-15.
//

#ifndef MACHIAVELLI_GAMECONTROLLER_H
#define MACHIAVELLI_GAMECONTROLLER_H


#include <memory>
#include <vector>
#include <random>
#include <sstream>
#include "../models/BuildingCard.h"
#include "../models/CharacterCard.h"
#include "../models/Player.hpp"
#include "../lib/Socket.h"
#include "../lib/ClientCommand.h"

class GameController {
private:
    std::vector<std::shared_ptr<BuildingCard>> buildingCards;
    std::vector<std::shared_ptr<CharacterCard>> characterCards;
    std::vector<std::shared_ptr<CharacterCard>> availableCards;
    std::vector<std::shared_ptr<CharacterCard>> overViewCard;
    std::vector<BuildingColor> buildingColors;
    std::random_device dev;
    std::default_random_engine dre{dev()};
    std::vector<std::shared_ptr<Player>> players;
    int nextBuildingCard;
    int nextCharacterCard;
    std::vector<std::shared_ptr<Socket>> sockets;
    bool isInSetup;
    bool isPlaying;
    bool canBuild;
    bool firstCard;
    bool firstTurn;
    bool secondCard;
    bool lastRound;
    bool lastCommand;
    int goldCoins;

public:
    void init();

    void readCardsFromFile();

    std::vector<std::vector<std::string>> getNextLineAndSplitIntoTokens(const std::string pathToFile);

    void initBuildingCards();

    void initCharacterCards();

    void playRandomCards();

    void getRandomCharacterCard(std::shared_ptr<Player> player);

    std::shared_ptr<BuildingCard> getRandomBuildingCard();

    void doNextTurn();

    void doPlayerTurn(std::shared_ptr<Player> player, std::shared_ptr<CharacterCard>);

    void setNextKing();

    void playRandomBuildingCards();

    void playRandomCharacterCards();


    bool isCanBuild() const {
        return canBuild;
    }

    void setCanBuild(bool canBuild) {
        GameController::canBuild = canBuild;
    }

    std::vector<std::shared_ptr<Socket>> &getSockets() {
        return sockets;
    }

    std::vector<std::shared_ptr<Player>> &getPlayers() {
        return players;
    }

    void showUI(std::shared_ptr<Player> player);

    void showGameUI(std::shared_ptr<Player> p, std::shared_ptr<CharacterCard>);

    void setUpRound();


    bool isIsInSetup() const {
        return isInSetup;
    }

    void setIsInSetup(bool isInSetup) {
        GameController::isInSetup = isInSetup;
    }


    bool isLastCommand() const {
        return lastCommand;
    }

    bool isLastRound() const {
        return lastRound;
    }

    void setLastRound(bool lastRound) {
        GameController::lastRound = lastRound;
    }

    bool isIsPlaying() const {
        return isPlaying;
    }

    void setIsPlaying(bool isPlaying) {
        GameController::isPlaying = isPlaying;
    }

    void pickCard(int index, std::shared_ptr<Player> player);

    void removeCard(int index, std::shared_ptr<Player> player);

    void showAvailableCards(std::shared_ptr<Player> currentPlayer);

    void pickOneCardToKeep(std::shared_ptr<Player> currentPlayer);

    void pickOneCardToRemove(std::shared_ptr<Player> currentPlayer);


    bool isFirstCard() const {
        return firstCard;
    }

    void setFirstCard(bool firstCard) {
        GameController::firstCard = firstCard;
    }

    bool isSecondCard() const {
        return secondCard;
    }

    void setSecondCard(bool secondCard) {
        GameController::secondCard = secondCard;
    }

    void goToNextPlayerInSetup();

    void doTurn();

    void calculatePoints(std::shared_ptr<Player> p);


    int getGoldCoins() const {
        return goldCoins;
    }

    void setGoldCoins(int goldCoins) {
        GameController::goldCoins = goldCoins;
    }


    void setLastCommand(bool lastCommand) {
        GameController::lastCommand = lastCommand;
    }

    bool isFirstTurn() const {
        return firstTurn;
    }

    void setFirstTurn(bool firstTurn) {
        GameController::firstTurn = firstTurn;
    }

    void addCoins(std::shared_ptr<Player> p, int amount);

    void getTwoBuildingCardsAndPutOneBack(std::shared_ptr<Player> p);

    void handleCommand(ClientCommand command);

    void getNextCharacterCard();

    void goToNextPlayerInGame(std::shared_ptr<Player>);

    void removePlayer(std::shared_ptr<Player> player);

    void getOpponentDetails(std::shared_ptr<Player> player);

    void showOverview(std::shared_ptr<Player> player);

    std::shared_ptr<Player> getOpponent(std::shared_ptr<Player> player);

    void showPossibleBuildings(std::shared_ptr<Player> player);

    void buildBuilding(int option, std::shared_ptr<Player> player);

    void determineWinner();

    void calculatePointsByBuildings(std::shared_ptr<Player> player);

    void setFirstToFinish(std::shared_ptr<Player> p);

    void showEndGameText(std::shared_ptr<Player> player);

    void showEndGameText(std::shared_ptr<Player> winner, bool isDraw);

    void addExtraGold(std::shared_ptr<Player> player, std::shared_ptr<CharacterCard> cc);

    void showLastTimeSpecialAbilityOption(std::shared_ptr<Player> player);
};


#endif //MACHIAVELLI_GAMECONTROLLER_H
