//
// Created by ronald on 21-12-15.
//

#include "BuildingCardFactory.h"

using namespace std;

shared_ptr<BuildingCardFactory> BuildingCardFactory::instance = nullptr;

BuildingCardFactory::BuildingCardFactory() {
    init();
}

std::shared_ptr<BuildingCardFactory> BuildingCardFactory::getInstance() {
    if(!instance){
        instance = shared_ptr<BuildingCardFactory>(new BuildingCardFactory);
    }

    return instance;
}

void BuildingCardFactory::init() {
    colorRegistry.insert({"geel", BuildingColor::YELLOW});
    colorRegistry.insert({"groen", BuildingColor::GREEN});
    colorRegistry.insert({"rood", BuildingColor::RED});
    colorRegistry.insert({"blauw", BuildingColor::BLUE});
    colorRegistry.insert({"lila", BuildingColor::LILA});

    typeRegistry.insert({"Landgoed", BuildingType::ESTATE});
    typeRegistry.insert({"Kasteel", BuildingType::CHATEAU});
    typeRegistry.insert({"Paleis", BuildingType::PALACE});
    typeRegistry.insert({"Taveerne", BuildingType::TAVERN});
    typeRegistry.insert({"Markt", BuildingType::MARKET});
    typeRegistry.insert({"Winkels", BuildingType::STORES});
    typeRegistry.insert({"Handelshuis", BuildingType::COMMERCE_CENTER});
    typeRegistry.insert({"Haven", BuildingType::DOCK});
    typeRegistry.insert({"Raadhuis", BuildingType::TOWN_HALL});
    typeRegistry.insert({"Tempel", BuildingType::TEMPLE});
    typeRegistry.insert({"Kerk", BuildingType::CHURCH});
    typeRegistry.insert({"Klooster", BuildingType::MONASTERY});
    typeRegistry.insert({"Kathedraal", BuildingType::CATHEDRAL});
    typeRegistry.insert({"Wachttoren", BuildingType::WATCH_TOWER});
    typeRegistry.insert({"Gevangenis", BuildingType::PRISON});
    typeRegistry.insert({"Toernooiveld", BuildingType::TOURNAMENT_FIELD});
    typeRegistry.insert({"Burcht", BuildingType::CASTLE});
    typeRegistry.insert({"Hof der Wonderen", BuildingType::COURTYARD_OF_WONDERS});
    typeRegistry.insert({"Kerker", BuildingType::DUNGEON});
    typeRegistry.insert({"Kerkhof", BuildingType::CEMETERY});
    typeRegistry.insert({"Laboratorium", BuildingType::LABORATORY});
    typeRegistry.insert({"Werkplaats", BuildingType::WORKSHOP});
    typeRegistry.insert({"Observatorium", BuildingType::OBSERVATORY});
    typeRegistry.insert({"Bibliotheek", BuildingType::LIBRARY});
    typeRegistry.insert({"School voor magiërs", BuildingType::MAGICIANS_SCHOOL});
    typeRegistry.insert({"Drakenpoort", BuildingType::DRAGON_GATE});
    typeRegistry.insert({"Universiteit", BuildingType::UNIVERSITY});
}
