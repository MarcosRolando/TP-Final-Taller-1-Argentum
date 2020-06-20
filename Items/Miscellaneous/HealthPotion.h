//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_HEALTHPOTION_H
#define ARGENTUM_HEALTHPOTION_H


#include "Potion.h"

class HealthPotion: public Potion {
private:
    void restoreStat(Player& player) override;
public:
    HealthPotion();
};


#endif //ARGENTUM_HEALTHPOTION_H
