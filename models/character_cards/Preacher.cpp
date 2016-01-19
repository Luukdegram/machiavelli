//
// Created by ronald on 21-12-15.
//

#include "Preacher.h"
using namespace std;

void Preacher::countBlueBuildings(std::shared_ptr<Player> player) {
    int extraCoins = 0;
    for(shared_ptr<BuildingCard> card : player->getBuildBuildings()) {
        if (card->getColor() == BuildingColor::BLUE) {
            extraCoins ++;
        }
    }

    player->setGoldCoins(player->getGoldCoins() + extraCoins);
}

void Preacher::doSpecialAbility(std::shared_ptr<Player> player, std::string string, shared_ptr<GameController> gameController) {
    CharacterCard::doSpecialAbility(player, string, gameController);
    countBlueBuildings(player);

    if(player->isChoseMainOption()){
        gameController->getNextCharacterCard();
    }else{
        gameController->showGameUI(player, std::shared_ptr<CharacterCard>(this));
    }
}
