//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_POTION_H
#define ARGENTUM_POTION_H


#include "../Item.h"
#include "../../Config/Configuration.h"
#include "../../Entities/Player.h"

class Potion: public Item {
protected:
    unsigned int recoveryValue;
public:
    explicit Potion(const Config::PotionData& data);
    EquipmentPlace use(Player& player) override;
    virtual void restoreStat(Player& player) = 0;
};


#endif //ARGENTUM_POTION_H
