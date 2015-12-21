//
// Created by ronald on 16-12-15.
//

#ifndef MACHIAVELLI_BUILDINGCARD_H
#define MACHIAVELLI_BUILDINGCARD_H

#include <string>
#include <map>
#include "BaseCard.h"
#include "BuildingType.h"
#include "BuildingColor.h"

class BuildingCard : public BaseCard {

private:
    BuildingColor color;
    BuildingType buildingType;
    std::string description;
    std::string name;
public:
    BuildingCard(std::string _color, std::string _type, int _value, std::string _description);
    BuildingCard(std::string color, std::string type, int value);

    void setColor(std::string);


    const BuildingColor &getColor() const {
        return color;
    }

    void setColor(const BuildingColor &color) {
        BuildingCard::color = color;
    }

    const std::string &getDescription() const {
        return description;
    }

    void setDescription(const std::string &description) {
        BuildingCard::description = description;
    }


    const BuildingType &getBuildingType() const {
        return buildingType;
    }

    const std::string &getName() const {
        return name;
    }

    void setType(std::string type);
};


#endif //MACHIAVELLI_BUILDINGCARD_H
