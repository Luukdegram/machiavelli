//
// Created by ronald on 16-12-15.
//

#ifndef MACHIAVELLI_CHARACTERCARD_H
#define MACHIAVELLI_CHARACTERCARD_H

#include <string>
#include <map>
#include "BaseCard.h"
#include "CharacterType.h"
#include "Player.hpp"
#include "../controller/GameController.h"


class CharacterCard : public BaseCard {

protected:
    std::string name;
    CharacterType characterType;
    bool isKilled;
    bool isRobbed;

public:
    CharacterCard(int value, const std::string &name);

public:
    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        CharacterCard::name = name;
    }

    void setCharacterType(const CharacterType &characterType) {
        CharacterCard::characterType = characterType;
    }

    const CharacterType &getCharacterType() const {
        return characterType;
    }

    bool isIsKilled() const {
        return isKilled;
    }

    void setIsKilled(bool isKilled) {
        CharacterCard::isKilled = isKilled;
    }

    bool isIsRobbed() const {
        return isRobbed;
    }

    void setIsRobbed(bool isRobbed) {
        CharacterCard::isRobbed = isRobbed;
    }

    virtual void doSpecialAbility(std::shared_ptr<Player>, std::string command, std::shared_ptr<GameController> gameController);
};


#endif //MACHIAVELLI_CHARACTERCARD_H
