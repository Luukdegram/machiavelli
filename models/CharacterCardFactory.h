//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_CHARACTERCARDFACTORY_H
#define MACHIAVELLI_CHARACTERCARDFACTORY_H

#include <memory>
#include "CharacterCard.h"

class CharacterCardFactory {

private:
    static std::shared_ptr<CharacterCardFactory> instance;
    std::map<std::string, std::shared_ptr<CharacterCard>> registry;
    std::map<std::string,CharacterType> typeRegistry;

protected:
    CharacterCardFactory();

public:
    static std::shared_ptr<CharacterCardFactory> getInstance();
    std::shared_ptr<CharacterCard> createCharacterCard(std::string, std::string);
    void init();
};


#endif //MACHIAVELLI_CHARACTERCARDFACTORY_H
