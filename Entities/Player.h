//
// Created by agustin on 8/6/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H


#include "../Items/Inventory.h"
#include "Entity.h"

enum Direction{
    DIRECTION_UP, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT
};


class Player: public Entity {
private:
    Inventory inventory;
    /*
    unsigned int currentMana;
    //unsigned int maxMana;
    unsigned int currentHealth;
    //unsigned int maxHealth;
    unsigned int level;
    unsigned int experience;
    */
    unsigned int gold;
public:
    Player(unsigned int maxHealth, unsigned int maxMana, Coordinate initialPosition);

    //Modifica la posicion almacenada por el jugador, para que luego sea actualizada
    //por el juego
    void move(Direction direction);


    bool isMonsterTarget() override;

    //IMPLEMENTAR
    void attack(Coordinate target);

    //Si hay lugar en el inventario del player entonces se apropia del item y
    //retorna true, sino no se apropia de el y retorna false
    bool storeItem(std::shared_ptr<Item>&& item);

    //Retorna el item que almacene el inventario al pedirle el item con nombre
    //itemName
    std::shared_ptr<Item> removeItem(const std::string& itemName);

    //Intenta reducir en ammount la cantidad de oro que guarda, si esta es menor
    //que ammount entonces no la reduce y retorna false, sino la reduce y retorna
    //true
    bool spendGold(unsigned int ammount);

    void receiveGold(unsigned int ammount);
};


#endif //ARGENTUM_PLAYER_H
