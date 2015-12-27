//
// Created by ronald on 21-12-15.
//

#include "Magician.h"
#include "../CharacterCardFactory.h"

using namespace std;

void Magician::doSpecialAbility(std::shared_ptr<Player> player, std::string command) {
    handleSpecialAbility(player, command);
}

void Magician::handleSpecialAbility(std::shared_ptr<Player> player, std::string command) {
    shared_ptr<Socket> client = player->getClient();

    client->write("Please select an option: \r\n");
    client->write("[0] Swap all your hand cards with your opponent's \n");
    client->write("[1] Swap a number of your cards to obtain building cards \n");
    client->write("machiavelli>");
    int option = stoi(string{client->readline()});

    if(option == 0) {
        //TODO: Need access to gamecontroller for opponent's cards
    }else if(option == 1) {
        client->write("How many cards would you like to swap for building cards? \n");
        int amount = stoi(string{client->readline()});

        if(amount > player->getCharacterCards().size()) {
            amount = player->getCharacterCards().size();
        }

        //TODO: Need access to gamecontroller for building cards
    } else {
        client->write("Invalid option, try again. \r\n");
        handleSpecialAbility(player, command);
    }

}
