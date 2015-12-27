//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_MAGICIAN_H
#define MACHIAVELLI_MAGICIAN_H


#include "../CharacterCard.h"

class Magician : public CharacterCard {

public:
    Magician(int value, const std::string &name) : CharacterCard(value, name) { }

    void doSpecialAbility(std::shared_ptr<Player> player, std::string command);
    void handleSpecialAbility(std::shared_ptr<Player> player, std::string command);
};


#endif //MACHIAVELLI_MAGICIAN_H
