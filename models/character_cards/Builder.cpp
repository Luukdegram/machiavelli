//
// Created by ronald on 21-12-15.
//

#include "Builder.h"

using namespace std;

void Builder::doSpecialAbility(std::shared_ptr<Player> player, std::string command,
                               std::shared_ptr<GameController> gameController) {
    CharacterCard::doSpecialAbility(player, command, gameController);

    // Give player 2 building cards
    player->getBuildingCards().push_back(gameController->getRandomBuildingCard());
    player->getBuildingCards().push_back(gameController->getRandomBuildingCard());

    buildBuilding(player, 0);

    if(player->isChoseMainOption()){
        gameController->getNextCharacterCard();
    }else{
        gameController->showGameUI(player, std::shared_ptr<CharacterCard>(this));
    }
}

void Builder::buildBuilding(std::shared_ptr<Player> player, int count) {
    player->getClient()->write("Do you want to build buildings?\r\n");
    player->getClient()->write("[0] Yes\r\n");
    player->getClient()->write("[1] No\r\n");

    int answer = stoi(player->getClient()->readline());

    if(answer == 0) {
        shared_ptr<Socket> client = player->getClient();

        client->write("Which building would you like to build? \r\n");
        int counter = 1;
        for (shared_ptr<BuildingCard> card : player->getBuildingCards()) {
            client->write("[" + to_string(counter) + "]" + card->getName() + "\r\n");
            counter++;
        }

        answer = stoi(client->readline()) - 1;

        if (answer >= player->getBuildingCards().size()) {
            client->write("Invalid option! \r\n");
            buildBuilding(player, count);
        }


        player->buildBuilding(player->getBuildingCards().at(answer));
        count++;

        if(count < 3) {
            buildBuilding(player, count);
        }
    } else {
        player->getClient()->write("You have chosen no \n");
    }
}
