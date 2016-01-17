//
// Created by ronald on 21-12-15.
//

#include <iostream>
#include "Thief.h"
#include "../CharacterCardFactory.h"
#include "../CharacterType.h"

using namespace std;

void Thief::doSpecialAbility(shared_ptr<Player> player, std::string command, shared_ptr<GameController> gameController) {
    CharacterCard::doSpecialAbility(player, command, gameController);

    std::map<string, CharacterType> types = CharacterCardFactory::getInstance()->getTypeRegistry();

    player->getClient()->write("Chose a card to steal from: \n");
    for(auto card : types)
    {
        if(card.second != CharacterType::ASSASSIN) {
            player->getClient()->write(card.first + "\n");
        }
    }

    string answer = player->getClient()->readline();
    if(types[answer] != CharacterType::INVALID) {
        gameController->getOpponent(player)->setStolen(types[answer]);
        player->getClient()->write("Successfully robbed from the card \n");
    } else {
        Thief::doSpecialAbility(player, command, gameController);
    }
}
