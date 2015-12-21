//
// Created by ronald on 16-12-15.
//

#ifndef MACHIAVELLI_CHARACTERCARD_H
#define MACHIAVELLI_CHARACTERCARD_H

#include <string>
#include "BaseCard.h"


class CharacterCard : public BaseCard {
private:
    std::string name;


public:
    CharacterCard(int value, const std::string &name);

public:
    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        CharacterCard::name = name;
    }
};


#endif //MACHIAVELLI_CHARACTERCARD_H
