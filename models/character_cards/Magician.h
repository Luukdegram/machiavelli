//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_MAGICIAN_H
#define MACHIAVELLI_MAGICIAN_H


#include "../CharacterCard.h"

class Magician : public CharacterCard {

public:
    Magician(int value, const std::string &name) : CharacterCard(value, name) { }

    virtual void doSpecialAbility(std::shared_ptr<Player> player, std::string command, std::shared_ptr<GameController> gameController);
    void handleSpecialAbility(std::shared_ptr<Player> player, std::string command, std::shared_ptr<GameController> gameController);
};


#endif //MACHIAVELLI_MAGICIAN_H
