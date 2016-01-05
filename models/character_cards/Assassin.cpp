//
// Created by ronald on 21-12-15.
//

#include <iostream>
#include "Assassin.h"
#include "../CharacterCardFactory.h"

using namespace std;


void Assassin::doSpecialAbility(shared_ptr<Player> player, std::string command, shared_ptr<GameController> gameController) {
    CharacterCard::doSpecialAbility(player, command, gameController);

    if(gameController->getOpponent(player)->getCharacter()->getCharacterType() != CharacterType::CONDOTTIERI) {
        gameController->getOpponent(player)->setKilled(true);
    }

    player->getClient()->write("Successfully killed the opponent.\n");
}
