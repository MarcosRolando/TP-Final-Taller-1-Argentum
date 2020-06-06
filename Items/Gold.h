//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_GOLD_H
#define ARGENTUM_GOLD_H


#include "Item.h"

//Clase que representa un puniado de oro en el piso
class Gold: public Item{
private:
    unsigned int ammount;

public:
    explicit Gold(unsigned int ammount = 0);

    void use(int &player) override;

    unsigned int getAmmount();
};

#endif //ARGENTUM_GOLD_H
