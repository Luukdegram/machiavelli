//
// Created by ronald on 16-12-15.
//

#include "BuildingCard.h"

using namespace std;

void BuildingCard::setColor(string string) {
    if(string.compare("groen") == 0){
        color = GREEN;
    }else if(string.compare("rood") == 0){
        color = RED;
    }else if(string.compare("blauw") == 0){
        color = BLUE;
    }else{
        color = YELLOW;
    }
}

void BuildingCard::setType(std::string type){

}

BuildingCard::BuildingCard(std::string color, std::string type, int value){

}

BuildingCard::BuildingCard(std::string color, std::string type, int value, std::string description) {

}
