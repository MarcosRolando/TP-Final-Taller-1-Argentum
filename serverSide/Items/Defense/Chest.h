//
// Created by agustin on 9/6/20.
//

#ifndef ARGENTUM_CHEST_H
#define ARGENTUM_CHEST_H

#include "Clothing.h"

class ItemTests;

/*Esta clase encapsula el comportamiento particular de la ropa equipable
 * en el chest*/

class Chest: public Clothing {
private:
    friend ItemTests;

public:
    explicit Chest(GameType::Clothing clothing) : Clothing(clothing) {}

    /*Retorna la posicion donde se equipa (como es un chest retornara la posicion del chest)
     * Esto es util para saber en ejecucion donde se equipa el item ya que lo guardamos
     * en el padre*/
    GameType::EquipmentPlace use(Player& player) override;

    /*Esta funcion existe para que cuando el juegador muera y tire todos sus
    items no tire los items default*/
    bool isDefault() const override;
};


#endif //ARGENTUM_CHEST_H
