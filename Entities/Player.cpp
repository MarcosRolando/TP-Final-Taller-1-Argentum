//
// Created by agustin on 8/6/20.
//

#include "Player.h"

using namespace Config;

////////////////////////////////////PUBLIC///////////////////////////////

Player::Player(Race _race, Class _class, unsigned int _level, unsigned int _experience
            , Coordinate _initialPosition):
               Entity(_initialPosition), stats(_race, _class, _level, _experience) {
    gold = 0; //todo habria que recibir la cantidad de oro tambien,
                //todo o pasar por referencia la clase que maneje el archivo de
                //todo persistencia directamente
}

void Player::move(Direction direction) {
    switch (direction) {
        case DIRECTION_UP:
            currentPosition.jPosition--;
            break;
        case DIRECTION_DOWN:
            currentPosition.jPosition++;
            break;
        case DIRECTION_LEFT:
            currentPosition.iPosition++;
            break;
        case DIRECTION_RIGHT:
            currentPosition.iPosition--;
            break;
    }
}

void Player::attack(Coordinate target) {
    //IMPLEMENTAR
}

bool Player::isMonsterTarget() {
    return true;
}

bool Player::spendGold(unsigned int ammount) {
    if (ammount <= gold) {
        gold -= ammount;
        return true;
    }
    return false;
}

void Player::receiveGold(unsigned int ammount) {
    gold += ammount;
}

