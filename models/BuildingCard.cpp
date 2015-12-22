//
// Created by ronald on 16-12-15.
//

#include "BuildingCard.h"
#include "BuildingColor.h"
#include "BuildingCardFactory.h"

using namespace std;



BuildingCard::BuildingCard(std::string color, std::string type, int value):  name(type), colorName(color) {
    setValue(value);
    setColor(color);
    setType(type);
}

BuildingCard::BuildingCard(std::string color, std::string type, int value, std::string description) : description(description), name(type), colorName(color) {
    setValue(value);
    setColor(color);
    setType(type);
}

void BuildingCard::setColor(string type) {
    color = BuildingCardFactory::getInstance()->getColorRegistry().at(type);
}

void BuildingCard::setType(std::string type) {
    buildingType = BuildingCardFactory::getInstance()->getTypeRegistry().at(type);
}


