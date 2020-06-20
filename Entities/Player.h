//
// Created by agustin on 8/6/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H


#include "../Items/Inventory.h"
#include "Entity.h"
#include "PlayerStats.h"

class Game;

class Player: public Entity {
private:
    Inventory inventory;
    PlayerStats stats;
    unsigned int gold;
    Game& game;
    std::string nickname;

public:
    Player(Game& _game, Config::Race _race, Config::Class _class, unsigned int _level,
           unsigned int _experience, Coordinate _initialPosition, const std::string& nickname);


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

    AttackResult attacked(int damage, unsigned int attackerLevel) override;

    const std::string& getNickname() const;

    //Restaura hasta amount cantidad de vida, sin pasarse de la cantidad maxima
    void restoreLife(unsigned int amount);

    //Restaura hasta amount cantidad de mana, sin pasarse de la cantidad maxima
    void restoreMana(unsigned int amount);

private:
    void _dropItems();
};


#endif //ARGENTUM_PLAYER_H
