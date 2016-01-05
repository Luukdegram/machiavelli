//
// Created by ronald on 21-12-15.
//

#include <iostream>
#include "Thief.h"
#include "../CharacterCardFactory.h"

using namespace std;

void Thief::doSpecialAbility(shared_ptr<Player> player, std::string command, shared_ptr<GameController> gameController) {
    CharacterCard::doSpecialAbility(player, command, gameController);

    if(gameController->getOpponent(player)->getCharacter()->getCharacterType() != CharacterType::ASSASSIN) {
        gameController->getOpponent(player)->setStolen(true);
    }

    player->getClient()->write("Successfully robbed the opponent.\n");
}
