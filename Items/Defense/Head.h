//
// Created by agustin on 9/6/20.
//

#ifndef ARGENTUM_HEAD_H
#define ARGENTUM_HEAD_H


#include "Clothing.h"

class ItemTests;

class Head: public Clothing {
private:
    friend ItemTests;

public:
    explicit Head(GameType::Clothing clothing);

    GameType::EquipmentPlace use(Player& player) override;

    bool isDefault() const override;
};


#endif //ARGENTUM_HEAD_H
