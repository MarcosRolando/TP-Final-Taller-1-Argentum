//
// Created by agustin on 9/6/20.
//

#ifndef ARGENTUM_SHIELD_H
#define ARGENTUM_SHIELD_H


#include "Clothing.h"

class ItemTests;

class Shield: public Clothing {
private:
    friend ItemTests;

public:
    //Shield(unsigned int minDefense, unsigned int maxDefense);
    //explicit Shield(const Config::ClothingData& stats);
    explicit Shield(GameType::Clothing clothing);

    GameType::EquipmentPlace use(Player& player) override;

    bool isDefault() const override;
};


#endif //ARGENTUM_SHIELD_H
