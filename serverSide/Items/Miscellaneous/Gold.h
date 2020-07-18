//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_GOLD_H
#define ARGENTUM_GOLD_H


#include "../Item.h"

class ItemTests;

/*Clase que representa un puniado de oro en el piso*/

class Gold: public Item {
private:
    unsigned int amount;

    friend ItemTests;

public:
    explicit Gold(unsigned int amount);

    /*Retorna la posicion donde se equipa (como es oro no se equipa en ningun lado sino que
     * en realidad le sumamos a la cantidad de oro que guarda el player)*/
    GameType::EquipmentPlace use(Player& player) override;

    /*Retorna la cantidad de oro que representa la instancia Gold*/
    unsigned int getAmount() const;

    /* Retorna true, no es la solucion mas limpia pero era la mas sencilla de
     * implementar. Esto soluciona el tema donde el gold en realidad no va equipado en si
     * asi que no lo agregamos al inventario, pero como hereda de item necesitabamos
     * poder distinguir si era o no oro para sumarle a la variable del player*/
    bool isGold() const override;
};

#endif //ARGENTUM_GOLD_H
