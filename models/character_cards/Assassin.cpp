//
// Created by ronald on 21-12-15.
//

#include <iostream>
#include "Assassin.h"
#include "../CharacterCardFactory.h"

using namespace std;

void Assassin::doSpecialAbility(std::string command) {
    assassinate(command);
}

CharacterType Assassin::assassinate(string command){
    try {
        return CharacterCardFactory::getInstance()->getTypeRegistry().at(command);
    }catch(exception e){
      cout << e.what();
    }
}