//
// Created by ronald on 21-12-15.
//

#include <iostream>
#include "Thief.h"
#include "../CharacterCardFactory.h"

using namespace std;

CharacterType Thief::steal(string command) {
    CharacterType type;
  try{
    type = CharacterCardFactory::getInstance()->getTypeRegistry().at(command);
  }catch (exception e){
      cout << e.what();
      return CharacterType::INVALID;
  }

    if(type == CharacterType::ASSASSIN){
        cout << "You cannot robe the assassin!" << endl;
        return CharacterType::INVALID;
    }

    //TODO check in the GameController if the character isn't dead.
    return type;
}

void Thief::doSpecialAbility(string command) {
    steal(command);
}
