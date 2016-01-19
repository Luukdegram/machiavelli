//
// Created by ronald on 21-12-15.
//

#include <unistd.h>
#include "Magician.h"
#include "../CharacterCardFactory.h"

using namespace std;

void Magician::doSpecialAbility(std::shared_ptr<Player> player, std::string command, shared_ptr<GameController> gameController) {
    CharacterCard::doSpecialAbility(player, command, gameController);
    handleSpecialAbility(player, command, gameController);

    if(player->isChoseMainOption()){
        gameController->getNextCharacterCard();
    }else{
        gameController->showGameUI(player, std::shared_ptr<CharacterCard>(this));
    }
}

void Magician::handleSpecialAbility(std::shared_ptr<Player> player, std::string command, shared_ptr<GameController> gameController) {
    shared_ptr<Socket> client = player->getClient();

    client->write("Please select an option: \r\n");
    client->write("[0] Swap all your hand cards with your opponent's \n");
    client->write("[1] Swap a number of your cards to obtain building cards \n");
    client->write("machiavelli>");
    int option = stoi(string{client->readline()});

    if(option == 0) {
        vector<shared_ptr<CharacterCard>> tempCards = player->getCharacterCards();
        player->setCharacterCards(gameController->getOpponent(player)->getCharacterCards());
        gameController->getOpponent(player)->setCharacterCards(tempCards);
    }else if(option == 1) {
        client->write("How many cards would you like to swap for building cards? \n");
        int amount = stoi(string{client->readline()});

        if(amount > player->getCharacterCards().size()) {
            amount = player->getCharacterCards().size();
        }

        for(int i = 0; i < amount; i ++) {
            player->getBuildingCards().push_back(gameController->getRandomBuildingCard());
        }
    } else {
        client->write("Invalid option, try again. \r\n");
        handleSpecialAbility(player, command, gameController);
    }

}
