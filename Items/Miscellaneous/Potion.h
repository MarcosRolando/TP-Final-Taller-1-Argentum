//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_POTION_H
#define ARGENTUM_POTION_H


#include "../Item.h"
#include "../../Config/Configuration.h"

#include "../../Tests/ItemTests.h"


class Potion: public Item {
protected:
    unsigned int recoveryValue;

    friend ItemTests;

public:
    explicit Potion(const Config::PotionData& data);
    //explicit Potion(GameType::Potion potion);

    //Indica que una vez que son usadas las pociones son descartadas
    EquipmentPlace use(Player& player) override;

    //Debe llamar a la funcion de player que restaura el atributo correspondiente
    virtual void restoreStat(Player& player) = 0;
};


#endif //ARGENTUM_POTION_H
