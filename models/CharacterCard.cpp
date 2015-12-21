//
// Created by ronald on 16-12-15.
//

#include "CharacterCard.h"
#include <string>
using namespace std;

CharacterCard::CharacterCard(int value, const std::string &name) : name(name) {
    setValue(value);
}

void CharacterCard::specialAbility() {

}
