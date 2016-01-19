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
#include "BuildingCard.h"
#include "../lib/Socket.h"
#include "CharacterType.h"

class Player {
public:
	Player() {}
	Player(const std::string& name, std::shared_ptr<Socket> socket) : name {name}, client(socket) {setPoints(0);}
	
	std::string get_name() const { return name; }
	void set_name(const std::string& new_name) { name = new_name; }
	
private:
	std::shared_ptr<Socket> client;
	std::string name;
	std::vector<std::shared_ptr<BuildingCard>> buildingCards;
	std::vector<std::shared_ptr<class CharacterCard>> characterCards;
	std::vector<std::shared_ptr<BuildingCard>> buildBuildings;
    std::shared_ptr<CharacterCard> character;
	int goldCoins;
	bool isKing;
	bool firstToFinish;
	bool hasTurn;
	bool choseMainOption;
    bool blocked;
	int points;
    CharacterType stolen = CharacterType::INVALID;
    CharacterType killed = CharacterType::INVALID;
    bool usedAbility;
public:
	const std::string &getName() const {
		return name;
	}

	void setName(const std::string &name) {
		Player::name = name;
	}

    bool isBlocked() const {
        return blocked;
    }

    void setBlocked(bool blocked) {
        Player::blocked = blocked;
    }

    bool isUsedAbility() const {
        return usedAbility;
    }


	bool isChoseMainOption() const {
		return choseMainOption;
	}

	void setChoseMainOption(bool choseMainOption) {
		Player::choseMainOption = choseMainOption;
	}

	void setUsedAbility(bool usedAbility) {
        Player::usedAbility = usedAbility;
    }


    const CharacterType &getStolen() const {
        return stolen;
    }

    void setStolen(const CharacterType &stolen) {
        Player::stolen = stolen;
    }

    const CharacterType &getKilled() const {
        return killed;
    }

    void setKilled(const CharacterType &killed) {
        Player::killed = killed;
    }

    std::vector<std::shared_ptr<BuildingCard>> &getBuildBuildings() {
		return buildBuildings;
	}

	void setBuildBuildings(const std::vector<std::shared_ptr<BuildingCard>> &buildBuildings) {
		Player::buildBuildings = buildBuildings;
	}

	std::vector<std::shared_ptr<BuildingCard>> &getBuildingCards() {
		return buildingCards;
	}

	void setBuildingCards(const std::vector<std::shared_ptr<BuildingCard>> &buildingCards) {
		Player::buildingCards = buildingCards;
	}

	std::vector<std::shared_ptr<CharacterCard>> &getCharacterCards() {
		return characterCards;
	}

	void setCharacterCards(const std::vector<std::shared_ptr<CharacterCard>> &characterCards) {
		Player::characterCards = characterCards;
	}


    const std::shared_ptr<CharacterCard> &getCharacter() const {
        return character;
    }

    void setCharacter(const std::shared_ptr<CharacterCard> &character) {
        Player::character = character;
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


	const std::shared_ptr<Socket> &getClient() const {
		return client;
	}


	bool isHasTurn() const {
		return hasTurn;
	}

	void setHasTurn(bool hasTurn) {
		Player::hasTurn = hasTurn;
	}

	int getPoints() const {
		return points;
	}

	void setPoints(int points) {
		Player::points = points;
	}


	bool isFirstToFinish() const {
		return firstToFinish;
	}

	void setFirstToFinish(bool firstToFinish) {
		Player::firstToFinish = firstToFinish;
	}

    void buildBuilding(std::shared_ptr<BuildingCard> card);
    void removeBuilding(std::shared_ptr<BuildingCard> card);
};

#endif /* Player_hpp */
