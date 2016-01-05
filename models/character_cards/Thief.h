//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_THIEF_H
#define MACHIAVELLI_THIEF_H


#include "../CharacterCard.h"

class Thief : public CharacterCard {

public:
    Thief(int value, const std::string &name) : CharacterCard(value, name) { }

    virtual void doSpecialAbility(std::shared_ptr<Player>, std::string command, std::shared_ptr<GameController> gameController);
};


#endif //MACHIAVELLI_THIEF_H
