//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_WEAPON_H
#define ARGENTUM_WEAPON_H

#include "../Item.h"
#include "../../../libs/GameEnums.h"

class ItemTests;
class PlayerStats;
struct Coordinate;

/*Esta clase encapsula el comportamiento de las armas*/

class Weapon : public Item {
private:
    int minDamage{};
    int maxDamage{};
    unsigned int attackRange{};
    int manaConsumption{};

    friend ItemTests;

private:
    bool _isTargetReachable(Coordinate attackPosition, Coordinate attackedPosition) const;
    void _initializeData(int minDamage, int maxDamage,
                         unsigned int _manaConsumption, unsigned int _range);

public:
    explicit Weapon(GameType::Weapon weapon);

    /*Devuelve el danio que haria el arma por sí sola, es un numero aleatorio
    entre el danio minimo y el maximo
    Recibe las posiciones para determinar si el ataque es realizado o no, si
    no lo realiza retorna 0
    Podria recibir la distancia, pero esto permite encapsular la forma de
    calcular la distancia en la Weapon*/
    int getDamage(Coordinate attackPosition, Coordinate attackedPosition, PlayerStats& stats) const;

    /*Retorna la posicion donde se equipa (como esta es un arma sera en el lugar del arma)
     * Esto es util para saber en ejecucion donde se equipa el item ya que lo guardamos
     * en el padre*/
    GameType::EquipmentPlace use(Player& player) override;

    /*Esta funcion existe para que cuando el juegador muera y tire todos sus
    items no tire los items default*/
    bool isDefault();

    ~Weapon() override;
};


#endif //ARGENTUM_WEAPON_H
