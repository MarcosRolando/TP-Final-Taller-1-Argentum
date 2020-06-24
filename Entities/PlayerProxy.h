//
// Created by marcos on 23/6/20.
//

#ifndef ARGENTUM_PLAYERPROXY_H
#define ARGENTUM_PLAYERPROXY_H

#include <string>
#include "MoveDirection.h"
#include "../Items/Inventory.h"

class Player;
class Game;
struct Coordinate;

class PlayerProxy {
private:
    Game& game;
    Player& player;

public:
    explicit PlayerProxy(Game& _game, Player& _player) : game(_game), player(_player) {}
    void attack(Coordinate target);
    void useItem(int itemPosition);
    void meditate();
    void move(Direction direction);
    void buyFrom(std::string&& itemName, Coordinate npcPosition);
    void sellTo(std::string&& itemName, Coordinate npcPosition);
    void withdrawFrom(std::string&& itemName, Coordinate npcPosition);
    void listFrom(Coordinate npcPosition);
    void depositTo(std::string&& itemName, Coordinate npcPosition);
    void unequip();
    void unequip(EquipmentPlace clothing);
    void dropItem(unsigned int itemPosition);

};


#endif //ARGENTUM_PLAYERPROXY_H
