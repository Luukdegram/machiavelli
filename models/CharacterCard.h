//
// Created by ronald on 16-12-15.
//

#ifndef MACHIAVELLI_CHARACTERCARD_H
#define MACHIAVELLI_CHARACTERCARD_H

#include <string>
#include <map>
#include "BaseCard.h"
#include "CharacterType.h"


class CharacterCard : public BaseCard {

protected:
    std::string name;
    CharacterType characterType;
    bool isKilled;

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

    virtual void specialAbility();
};


#endif //MACHIAVELLI_CHARACTERCARD_H
