//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_MANAPOTION_H
#define ARGENTUM_MANAPOTION_H


#include "Potion.h"

class ManaPotion: public Potion {
private:
    void restoreStat(Player& player) override;

public:
    ManaPotion();
    ~ManaPotion() override;
};


#endif //ARGENTUM_MANAPOTION_H
