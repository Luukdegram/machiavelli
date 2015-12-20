//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <string>
#include <memory>
#include <vector>
#include "CharacterCard.h"
#include "BuildingCard.h"

class Player {
public:
	Player() {}
	Player(const std::string& name) : name {name} {}
	
	std::string get_name() const { return name; }
	void set_name(const std::string& new_name) { name = new_name; }
	
private:
	std::string name;
	std::vector<std::shared_ptr<BuildingCard>> buildingCards;
	std::shared_ptr<CharacterCard> characterCard;
	int goldCoins;
	bool isKing;


public:
	const std::string &getName() const {
		return name;
	}

	void setName(const std::string &name) {
		Player::name = name;
	}

	const std::vector<std::shared_ptr<BuildingCard>> &getBuildingCards() const {
		return buildingCards;
	}

	void setBuildingCards(const std::vector<std::shared_ptr<BuildingCard>> &buildingCards) {
		Player::buildingCards = buildingCards;
	}

	const std::shared_ptr<CharacterCard> &getCharacterCard() const {
		return characterCard;
	}

	void setCharacterCard(const std::shared_ptr<CharacterCard> &characterCard) {
		Player::characterCard = characterCard;
	}

	int getGoldCoins() const {
		return goldCoins;
	}

	void setGoldCoins(int goldCoins) {
		Player::goldCoins = goldCoins;
	}

	bool isIsKing() const {
		return isKing;
	}

	void setIsKing(bool isKing) {
		Player::isKing = isKing;
	}
};

#endif /* Player_hpp */
