//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_BUILDER_H
#define MACHIAVELLI_BUILDER_H


#include "../CharacterCard.h"

class Builder : public CharacterCard {

public:
    Builder(int value, const std::string &name) : CharacterCard(value, name) { }
};


#endif //MACHIAVELLI_BUILDER_H
