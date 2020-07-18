//
// Created by marcos on 20/6/20.
//

#ifndef ARGENTUM_MONSTERSTATS_H
#define ARGENTUM_MONSTERSTATS_H

#include "../../libs/GameEnums.h"
#include <string>

class EntityTests;
struct AttackResult;

class MonsterStats {
private:
    unsigned int constitution;
    unsigned int agility;
    unsigned int strength;
    int damage;
    unsigned int speed;

    unsigned int level;
    int currentLife;
    int maxLife;
    unsigned int rangeOfVision;

    friend EntityTests;

public:
    explicit MonsterStats(GameType::Entity type);

    /*Retorna el rango de vision del monster*/
    unsigned int getRangeOfVision() const;

    /*Retorna el danio del monster*/
    int getDamage() const;

    /*Retorna el nivel del monster*/
    unsigned int getLevel() const;

    /*Recibe el danio y modifica la vida del monster acorde a este, retorna luego
     * un pair con el danio neto recibido y un bool en true en caso de que haya
     * logrado esquivar el ataque (esto es asi ya que queda extendible por si el
     * monstruo pudiera tener defensa y el danio fuera 0 sin haber esquivado)*/
    std::pair<int, bool> modifyLife(int _damage);

    /*Retorna la vida actual del monstruo*/
    int getCurrentLife() const;

    /*Retorna la vida maxima del monstruo*/
    int getMaxLife() const;

    /*Retorna la agilidad del monstruo*/
    unsigned int getAgility() const;
};


#endif //ARGENTUM_MONSTERSTATS_H
