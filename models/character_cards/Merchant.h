//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_MERCHANT_H
#define MACHIAVELLI_MERCHANT_H


#include "../CharacterCard.h"

class Merchant : public CharacterCard {

public:
    Merchant(int value, const std::string &name) : CharacterCard(value, name) { }
};


#endif //MACHIAVELLI_MERCHANT_H
