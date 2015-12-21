//
// Created by ronald on 16-12-15.
//

#ifndef MACHIAVELLI_BASECARD_H
#define MACHIAVELLI_BASECARD_H

#include <string>
#include <map>

class BaseCard {
protected:
    int value;
    enum Color {YELLOW, BLUE, GREEN, RED, LILA};
//    enum BuildingType {ESTATE, CHÂTEAU, PALACE, TAVERN, MARKET, STORES, COMMERCE_CENTER, DOCK,
//        TOWN_HALL, TEMPLE, CHURCH, MONASTERY, CATHEDRAL, WATCH_TOWER, PRISON, TOURNAMENT_FIELD,
//        CASTLE, COURTYARD_OF_WONDERS, DUNGEON, CEMETERY, LABORATORY, WORKSHOP, OBSERVATORY,
//        MAGICIANS_SCHOOL, DRAGON_GATE, UNIVERSITY};

 //   std::map<std::string, BuildingType> buildingTypeRegistry;

public:
    int getValue() const {
        return value;
    }

    void setValue(int value) {
        BaseCard::value = value;
    }

    virtual void setType(std::string type);
};


#endif //MACHIAVELLI_BASECARD_H
