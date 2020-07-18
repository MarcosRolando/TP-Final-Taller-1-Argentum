//
// Created by agustin on 9/6/20.
//

#ifndef ARGENTUM_SHIELD_H
#define ARGENTUM_SHIELD_H


#include "Clothing.h"

class ItemTests;

/*Esta clase encapsula el comportamiento particular de los escudos*/

class Shield: public Clothing {
private:
    friend ItemTests;

public:
    explicit Shield(GameType::Clothing clothing): Clothing(clothing) {}

    /*Retorna la posicion donde se equipa (como es un shield retornara la posicion del shield)
    * Esto es util para saber en ejecucion donde se equipa el item ya que lo guardamos
    * en el padre*/
    GameType::EquipmentPlace use(Player& player) override;

    /*Esta funcion existe para que cuando el juegador muera y tire todos sus
    * items no tire los items default*/
    bool isDefault() const override;
};


#endif //ARGENTUM_SHIELD_H
