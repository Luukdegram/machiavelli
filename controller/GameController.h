//
// Created by ronald on 16-12-15.
//

#ifndef MACHIAVELLI_GAMECONTROLLER_H
#define MACHIAVELLI_GAMECONTROLLER_H


#include <memory>
#include <vector>
#include <sstream>
#include "../models/BuildingCard.h"
#include "../models/CharacterCard.h"

class GameController {
private:
    std::vector<std::shared_ptr<BuildingCard>> buildingCards;
    std::vector<std::shared_ptr<CharacterCard>> characterCards;

public:
    void init();

    void readCardsFromFile();

    std::vector<std::vector<std::string>> getNextLineAndSplitIntoTokens(const std::string pathToFile);

    void initBuildingCards();

    void initCharacterCards();
};


#endif //MACHIAVELLI_GAMECONTROLLER_H
