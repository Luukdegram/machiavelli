//
// Created by ronald on 21-12-15.
//

#ifndef MACHIAVELLI_BUILDINGCARDFACTORY_H
#define MACHIAVELLI_BUILDINGCARDFACTORY_H

#include <memory>
#include <map>
#include "BuildingColor.h"
#include "BuildingType.h"

class BuildingCardFactory {
private:
    static std::shared_ptr<BuildingCardFactory> instance;
    std::map<std::string, BuildingType> typeRegistry;
    std::map<std::string, BuildingColor> colorRegistry;

protected:
    BuildingCardFactory();

public:
    static std::shared_ptr<BuildingCardFactory> getInstance();
    void init();

    const std::map<std::string, BuildingType> &getTypeRegistry() const {
        return typeRegistry;
    }

    const std::map<std::string, BuildingColor> &getColorRegistry() const {
        return colorRegistry;
    }
};


#endif //MACHIAVELLI_BUILDINGCARDFACTORY_H
