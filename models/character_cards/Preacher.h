//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_PREACHER_H
#define MACHIAVELLI_PREACHER_H


#include "../CharacterCard.h"

class Preacher : public CharacterCard{

public:
    Preacher(int value, const std::string &name) : CharacterCard(value, name) { }

    void countBlueBuildings(std::shared_ptr<Player>);
    virtual void doSpecialAbility(std::shared_ptr<Player>, std::string, shared_ptr<GameController> gameController);
};


#endif //MACHIAVELLI_PREACHER_H
