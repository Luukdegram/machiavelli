//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_CONDOTIERRI_H
#define MACHIAVELLI_CONDOTIERRI_H


#include "../CharacterCard.h"

class Condotierri : public CharacterCard {

public:
    Condotierri(int value, const std::string &name) : CharacterCard(value, name) { }

    void removeBuilding(std::shared_ptr<Player> player, std::shared_ptr<GameController> gameController);
    void countRedBuildings(std::shared_ptr<Player> player);
    virtual void doSpecialAbility(std::shared_ptr<Player> player, std::string command, std::shared_ptr<GameController> gameController);
};


#endif //MACHIAVELLI_CONDOTIERRI_H
