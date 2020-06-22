//
// Created by agustin on 9/6/20.
//

#ifndef ARGENTUM_HEAD_H
#define ARGENTUM_HEAD_H


#include "Clothing.h"

class Head: public Clothing {
public:
    //Head(unsigned int minDefense, unsigned int maxDefense);
    //explicit Head(const Config::ClothingData& stats);
    explicit Head(GameType::Clothing clothing);

    EquipmentPlace use(Player& player) override;
};


#endif //ARGENTUM_HEAD_H