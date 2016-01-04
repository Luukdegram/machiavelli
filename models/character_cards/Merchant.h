//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_MERCHANT_H
#define MACHIAVELLI_MERCHANT_H


#include <memory>
#include "../CharacterCard.h"
#include "../Player.hpp"

class Merchant : public CharacterCard {

public:
    Merchant(int value, const std::string &name) : CharacterCard(value, name) { }

    void addCoins(std::shared_ptr<Player> p);

    virtual void doSpecialAbility(std::shared_ptr<Player>, std::string, std::shared_ptr<GameController> gameController);
};


#endif //MACHIAVELLI_MERCHANT_H
