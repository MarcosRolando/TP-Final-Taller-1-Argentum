//
// Created by agustin on 9/6/20.
//

#ifndef ARGENTUM_CHEST_H
#define ARGENTUM_CHEST_H


#include "Clothing.h"

#include "../../Tests/ItemTests.h"


class Chest: public Clothing {
private:
    friend ItemTests;

public:
    //Chest(unsigned int minDefense, unsigned int maxDefense);
    //explicit Chest(const Config::ClothingData& stats);
    explicit Chest(GameType::Clothing clothing);

    EquipmentPlace use(Player& player) override;

    bool isDefault() const override;
};


#endif //ARGENTUM_CHEST_H
