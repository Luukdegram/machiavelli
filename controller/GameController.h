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

class GameController {
private:
    std::vector<std::shared_ptr<BuildingCard>> buildingCards;
    std::vector<std::shared_ptr<CharacterCard>> characterCards;
    std::random_device dev;
    std::default_random_engine dre{dev()};
    std::vector<std::shared_ptr<Player>> players;
    int nextBuildingCard;
    int nextCharacterCard;

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

    void doPlayerTurn(std::shared_ptr<Player> player);

    void setNextKing();

    void playRandomBuildingCards();

    void playRandomCharacterCards();
};


#endif //MACHIAVELLI_GAMECONTROLLER_H
