//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_THIEF_H
#define MACHIAVELLI_THIEF_H


#include "../CharacterCard.h"

class Thief : public CharacterCard {

public:
    Thief(int value, const std::string &name) : CharacterCard(value, name) { }


    CharacterType steal(std::string command);

    virtual void doSpecialAbility(std::string command);
};


#endif //MACHIAVELLI_THIEF_H
