//
// Created by marcos on 20/6/20.
//

#ifndef ARGENTUM_MONSTERSTATS_H
#define ARGENTUM_MONSTERSTATS_H

#include "../Config/GameEnums.h"

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

public:
    explicit MonsterStats(GameType::Monster type);

    unsigned int getRangeOfVision() const;

    int getDamage() const;

    unsigned int getLevel() const;

    AttackResult modifyLife(int _damage, unsigned int attackerLevel);

    int getCurrentLife() const;

    unsigned int getMaxLife() const;

private:
    //Retorna true si el monstruo esta muerto, false si esta vivo
    bool _isDead() const;
};


#endif //ARGENTUM_MONSTERSTATS_H
