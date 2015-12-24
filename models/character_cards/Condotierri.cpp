//
// Created by ronald on 21-12-15.
//

#include "Condotierri.h"

using namespace std;

void Condotierri::doSpecialAbility(std::shared_ptr<Player> player, std::string command) {
    countRedBuildings(player);

    //TODO: REMOVE BUILDING FROM OTHER PLAYER
}

void Condotierri::countRedBuildings(std::shared_ptr<Player> player) {
    int extraCoins = 0;
    for(shared_ptr<BuildingCard> card : player->getBuildBuildings()) {
        if (card->getColor() == BuildingColor::RED) {
            extraCoins ++;
        }
    }

    player->setGoldCoins(player->getGoldCoins() + extraCoins);
}
