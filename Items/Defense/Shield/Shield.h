//
// Created by agustin on 9/6/20.
//

#ifndef ARGENTUM_SHIELD_H
#define ARGENTUM_SHIELD_H


#include "../Clothing.h"

class Shield: public Clothing {
public:
    //Shield(unsigned int minDefense, unsigned int maxDefense);
    explicit Shield(const Config::ClothingData& stats);

    EquipmentPlace use(Player& player) override;
};


#endif //ARGENTUM_SHIELD_H
