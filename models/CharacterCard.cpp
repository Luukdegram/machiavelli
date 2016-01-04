//
// Created by ronald on 16-12-15.
//

#include "CharacterCard.h"
#include "Player.hpp"
#include "../controller/GameController.h"
#include <string>
using namespace std;

CharacterCard::CharacterCard(int value, const std::string &name) : name(name) {
    setValue(value);
}

void CharacterCard::doSpecialAbility(shared_ptr<Player> ptr, std::string command, shared_ptr<GameController> gameController) {

}
