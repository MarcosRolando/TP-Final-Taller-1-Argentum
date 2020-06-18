//
// Created by agustin on 8/6/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H


#include "../Items/Inventory.h"
#include "Entity.h"
#include "Stats.h"
#include "../Game.h"

enum Direction{
    DIRECTION_UP, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT
};

class Player: public Entity {
private:
    Inventory inventory;
    Stats stats;
    unsigned int gold;
    Game& game;
public:
    Player(Game& _game, Config::Race _race, Config::Class _class, unsigned int _level,
           unsigned int _experience, Coordinate _initialPosition);

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

    //Intenta reducir en amount la cantidad de oro que guarda, si esta es menor
    //que amount entonces no la reduce y retorna false, sino la reduce y retorna
    //true
    bool spendGold(unsigned int amount);

    //Incrementa el oro del Player en cantidad amount
    void receiveGold(unsigned int amount);

    //Usa el item en la posicion indicada, si no hay un item en la posicion no
    //hace nada
    void useItem(int itemPosition);
};


#endif //ARGENTUM_PLAYER_H