//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_ASSASSIN_H
#define MACHIAVELLI_ASSASSIN_H


#include "../CharacterCard.h"

class Assassin : public CharacterCard {

public:
    Assassin(int value, const std::string &name) : CharacterCard(value, name) { }

    CharacterType assassinate(std::string command);

    virtual void doSpecialAbility(std::shared_ptr<Player>, std::string command);
};


#endif //MACHIAVELLI_ASSASSIN_H
