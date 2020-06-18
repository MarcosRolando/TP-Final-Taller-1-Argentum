//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_WEAPON_H
#define ARGENTUM_WEAPON_H


#include "../Item.h"
#include "../../Map/Coordinate.h"
#include "../../Config/Configuration.h"

class Weapon : public Item {
private:
    int minDamage;
    int maxDamage;
    unsigned int attackRange;
    unsigned int manaConsumption;

private:
    bool _isTargetReachable(Coordinate attackPosition, Coordinate attackedPosition) const;
    void _initializeData(int minDamage, int maxDamage,
                         unsigned int _manaConsumption, unsigned int _range);
public:
    explicit Weapon(const Config::WeaponData& stats);


    //VER SI SE HACE QUE EN VEZ DE RETORNAR 0 TIRE UNA EXCEPCION

    //Devuelve el danio que haria el arma por sí sola, es un numero aleatorio
    //entre el danio minimo y el maximo
    //Recibe las posiciones para determinar si el ataque es realizado o no, si
    //no lo realiza retorna 0
    //Podria recibir la distancia, pero esto permite encapsular la forma de
    //calcular la distancia en la Weapon
    int getDamage(Coordinate attackPosition, Coordinate attackedPosition) const;

    EquipmentPlace use(Player& player) override;

    virtual ~Weapon() override;
};


#endif //ARGENTUM_WEAPON_H