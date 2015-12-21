//
// Created by ronald on 16-12-15.
//

#ifndef MACHIAVELLI_BASECARD_H
#define MACHIAVELLI_BASECARD_H


class BaseCard {
protected:
    int value;


public:
    int getValue() const {
        return value;
    }

    void setValue(int value) {
        BaseCard::value = value;
    }
};


#endif //MACHIAVELLI_BASECARD_H
