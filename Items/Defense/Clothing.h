//
// Created by agustin on 9/6/20.
//

#ifndef ARGENTUM_CLOTHING_H
#define ARGENTUM_CLOTHING_H


#include "../Item.h"

class Clothing : public Item {
private:
    unsigned int minDefense;
    unsigned int maxDefense;
public:
    explicit Clothing(unsigned int minDefense, unsigned int maxDefense);

    unsigned int getDefense();

    //virtual EquipmentPlace use(Player& player) = 0;
};


#endif //ARGENTUM_CLOTHING_H
