//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_MAGICIAN_H
#define MACHIAVELLI_MAGICIAN_H


#include "../CharacterCard.h"

class Magician : public CharacterCard {

public:
    Magician(int value, const std::string &name) : CharacterCard(value, name) { }
};


#endif //MACHIAVELLI_MAGICIAN_H
