//
// Created by ronald on 21-12-15.
//

#include <iostream>
#include "Assassin.h"
#include "../CharacterCardFactory.h"

using namespace std;


void Assassin::doSpecialAbility(shared_ptr<Player> player, std::string command, shared_ptr<GameController> gameController) {
    CharacterCard::doSpecialAbility(player, command, gameController);

    std::map<string, CharacterType> types = CharacterCardFactory::getInstance()->getTypeRegistry();

    player->getClient()->write("Chose a card to kill: \n");
    for(auto card : types)
    {
        if(card.second != CharacterType::CONDOTTIERI) {
            player->getClient()->write(card.first + "\n");
        }
    }

    string answer = player->getClient()->readline();

    if(types[answer] != CharacterType::INVALID) {
        gameController->getOpponent(player)->setKilled(types[answer]);
        player->getClient()->write("Successfully killed the card \n");
    } else {
        Assassin::doSpecialAbility(player, command, gameController);
    }
}
