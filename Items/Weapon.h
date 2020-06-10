//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_WEAPON_H
#define ARGENTUM_WEAPON_H


#include "Item.h"

class Weapon: public Item {
private:
    unsigned int minDamage;
    unsigned int maxDamage;
    unsigned int attackRange;

private:
    bool _isTargetReachable(Coordinate attackPosition, Coordinate attackedPosition) const;

public:
    Weapon(unsigned int minDamage, unsigned int maxDamage);



    //VER SI SE HACE QUE EN VEZ DE RETORNAR 0 TIRE UNA EXCEPCION

    //Devuelve el danio que haria el arma por sí sola, es un numero aleatorio
    //entre el danio minimo y el maximo
    //Recibe las posiciones para determinar si el ataque es realizado o no, si
    //no lo realiza retorna 0
    //Podria recibir la distancia, pero esto permite encapsular la forma de
    //calcular la distancia en la Weapon
    unsigned int getDamage(Coordinate attackPosition, Coordinate attackedPosition) const;

    EquipmentPlace use(Player& player) override;
};


#endif //ARGENTUM_WEAPON_H
