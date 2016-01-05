//
// Created by ronald on 21-12-15.
//

#include "Condotierri.h"

using namespace std;

void Condotierri::doSpecialAbility(std::shared_ptr<Player> player, std::string command, shared_ptr<GameController> gameController) {
    CharacterCard::doSpecialAbility(player, command, gameController);
    countRedBuildings(player);
    removeBuilding(player, gameController);
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

void Condotierri::removeBuilding(std::shared_ptr<Player> player, std::shared_ptr<GameController> gameController) {
    shared_ptr<Socket> client = player->getClient();
    vector<shared_ptr<BuildingCard>> buildBuildings = gameController->getOpponent(player)->getBuildBuildings();

    client->write("Which building do you want to remove?\n");
    int counter = 0;
    for(shared_ptr<BuildingCard> card : buildBuildings) {
        client->write("[" + counter + "] " + card->getName());
    }

    int answer = stoi(client->readline());

    if(answer >= buildBuildings.size()) {
        client->write("Invalid option! \n");
        removeBuilding(player, gameController);
        return;
    }

    shared_ptr<BuildingCard> chosenCard = buildBuildings.at(answer);
    if(buildBuildings.size() < 8) {
        if (chosenCard->value > 1) {
            player->setGoldCoins(player->getGoldCoins() - chosenCard->value);
        }
        gameController->getOpponent(player)->removeBuilding(chosenCard);
        client->write("Removed opponent's card");
    } else {
        client->write("You can not remove buildings of a city that already has 8 buildings.\n");
    }

}
