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

    //buildingCards.erase(find(buildingCards.begin(), buildingCards.end(), card));
}
