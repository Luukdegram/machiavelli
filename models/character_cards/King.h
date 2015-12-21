//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_KING_H
#define MACHIAVELLI_KING_H


#include "../CharacterCard.h"

class King : public CharacterCard {

public:
    King(int value, const std::string &name) : CharacterCard(value, name) { }
};


#endif //MACHIAVELLI_KING_H
