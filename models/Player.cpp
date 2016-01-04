//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.hpp"

void Player::buildBuilding(std::shared_ptr<BuildingCard> card) {
    buildBuildings.push_back(card);

    int index;
    bool initialized = false;

    int counter = 0;
    for(std::shared_ptr<BuildingCard> current : buildingCards) {
        if(current == card) {
            index = counter;
            initialized = true;
        }

        counter ++;
    }

    // Make sure we delete correct card
    if(initialized) {
        buildingCards.erase(buildingCards.begin() + index);
    }
}
