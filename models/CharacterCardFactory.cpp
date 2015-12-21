//
// Created by ronald on 21-12-15.
//

#include "CharacterCardFactory.h"
#include "CharacterCard.h"
#include "character_cards/Thief.h"
#include "character_cards/Assassin.h"
#include "character_cards/Magician.h"
#include "character_cards/King.h"
#include "character_cards/Preacher.h"
#include "character_cards/Merchant.h"
#include "character_cards/Builder.h"
#include "character_cards/Condotierri.h"

using namespace std;

shared_ptr<CharacterCardFactory> CharacterCardFactory::instance = nullptr;

std::shared_ptr<CharacterCardFactory> CharacterCardFactory::getInstance() {
    if(!instance.get()){
        instance = shared_ptr<CharacterCardFactory>(new CharacterCardFactory);
    }

    return instance;
}

shared_ptr<CharacterCard> CharacterCardFactory::createCharacterCard(string name, string value){
    shared_ptr<CharacterCard> p;

    p = registry.at(name);
    p->setName(name);
    p->setValue(stoi(value));
    p->setCharacterType(typeRegistry.at(name));

    return p;
}

CharacterCardFactory::CharacterCardFactory() {
    init();
}

void CharacterCardFactory::init() {
    registry.insert({"Dief", shared_ptr<CharacterCard>(new Thief(0, ""))});
    registry.insert({"Moordenaar", shared_ptr<CharacterCard>(new Assassin(0, ""))});
    registry.insert({"Magiër", shared_ptr<CharacterCard>(new Magician(0, ""))});
    registry.insert({"Koning", shared_ptr<CharacterCard>(new King(0, ""))});
    registry.insert({"Prediker", shared_ptr<CharacterCard>(new Preacher(0, ""))});
    registry.insert({"Koopman", shared_ptr<CharacterCard>(new Merchant(0, ""))});
    registry.insert({"Bouwmeester", shared_ptr<CharacterCard>(new Builder(0, ""))});
    registry.insert({"Condottiere", shared_ptr<CharacterCard>(new Condotierri(0, ""))});

    typeRegistry.insert({"Dief", CharacterType::THIEF});
    typeRegistry.insert({"Moordenaar", CharacterType::ASSASSIN});
    typeRegistry.insert({"Magiër", CharacterType::MAGICIAN});
    typeRegistry.insert({"Koning", CharacterType::KING});
    typeRegistry.insert({"Prediker", CharacterType::PREACHER});
    typeRegistry.insert({"Koopman", CharacterType::MERCHANT});
    typeRegistry.insert({"Bouwmeester", CharacterType::BUILDER});
    typeRegistry.insert({"Condottiere", CharacterType::CONDOTTIERI});
}

