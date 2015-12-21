//
// Created by ronald on 16-12-15.
//

#ifndef MACHIAVELLI_BUILDINGCARD_H
#define MACHIAVELLI_BUILDINGCARD_H

#include <string>
#include <map>
#include "BaseCard.h"

class BuildingCard : public BaseCard {

private:
    Color color;
    std::string description;
public:
    BuildingCard(std::string _color, std::string _type, int _value, std::string _description);
    BuildingCard(std::string color, std::string type, int value);

    void setColor(std::string);

    void setType(std::string);

    const Color &getColor() const {
        return color;
    }

    void setColor(const Color &color) {
        BuildingCard::color = color;
    }

    const std::string &getDescription() const {
        return description;
    }

    void setDescription(const std::string &description) {
        BuildingCard::description = description;
    }
};


#endif //MACHIAVELLI_BUILDINGCARD_H
