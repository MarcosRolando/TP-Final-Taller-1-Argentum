//
// Created by agustin on 9/6/20.
//

#ifndef ARGENTUM_CHEST_H
#define ARGENTUM_CHEST_H


#include "Clothing.h"

class Chest: public Clothing {
public:
    //Chest(unsigned int minDefense, unsigned int maxDefense);
    //explicit Chest(const Config::ClothingData& stats);
    explicit Chest(GameType::Clothing clothing);

    EquipmentPlace use(Player& player) override;
};


#endif //ARGENTUM_CHEST_H
