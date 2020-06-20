//
// Created by marcos on 20/6/20.
//

#ifndef ARGENTUM_MONSTERSTATS_H
#define ARGENTUM_MONSTERSTATS_H


class MonsterStats {
private:
    unsigned int constitution;
    unsigned int intelligence;
    unsigned int agility;
    unsigned int strength;
    int damage;

    unsigned int level;
    int currentLife;
    int maxLife;
    unsigned int rangeOfVision;

public:
    explicit MonsterStats();


};


#endif //ARGENTUM_MONSTERSTATS_H
