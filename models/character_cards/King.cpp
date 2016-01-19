//
// Created by ronald on 21-12-15.
//

#include "King.h"
using namespace std;

void King::countBuildings(std::shared_ptr<Player> player) {
    int extraCoins = 0;
    for(shared_ptr<BuildingCard> card : player->getBuildBuildings()) {
        if (card->getColor() == BuildingColor::YELLOW) {
            extraCoins ++;
        }
    }

    player->setGoldCoins(player->getGoldCoins() + extraCoins);
}

void King::doSpecialAbility(std::shared_ptr<Player> player, std::string command,
                            std::shared_ptr<GameController> gameController) {
    CharacterCard::doSpecialAbility(player, command, gameController);

    countBuildings(player);

    if(player->isChoseMainOption()){
        gameController->getNextCharacterCard();
    }else{
        gameController->showGameUI(player, std::shared_ptr<CharacterCard>(this));
    }
}
