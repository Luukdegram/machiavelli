//
// Created by ronald on 21-12-15.
//

#include "Merchant.h"
#include <memory>
using namespace std;

void Merchant::doSpecialAbility(shared_ptr<Player> player, std::string string = "") {
    addCoins(player);
}

void Merchant::addCoins(std::shared_ptr<Player> p) {

  int extraGoldCoins = p->getGoldCoins() + 1;
  for(shared_ptr<BuildingCard> b : p->getBuildBuildings()){
     if(b->getColor() == BuildingColor::GREEN){
         extraGoldCoins++;
     }
  }
    p->setGoldCoins(extraGoldCoins);
}
