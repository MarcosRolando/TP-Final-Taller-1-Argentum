//
// Created by agustin on 14/6/20.
//

#ifndef ARGENTUM_PLAYERSTATS_H
#define ARGENTUM_PLAYERSTATS_H

#include "../Config/GameEnums.h"

//Clase que maneja el recibimiento de ataques, Player y Monster le delegan
//operaciones cuando deben modificar sus stats
class PlayerStats {
private:
    unsigned int generalTimer;
    unsigned int meditationTimer;
    bool isMeditating;

    unsigned int constitution;
    unsigned int intelligence;
    unsigned int agility;
    unsigned int strength;

    unsigned int classLifeMultiplier;
    unsigned int raceLifeMultiplier;
    unsigned int classManaMultiplier;
    unsigned int raceManaMultiplier;

    unsigned int experience;
    unsigned int nextLevelExperience;
    unsigned int level;
    unsigned int currentMana;
    int currentLife;
    unsigned int maxMana;
    int maxLife;

public:
    PlayerStats(GameType::Race _race, GameType::Class _class, unsigned int _level, unsigned int _experience);

    int getTotalDamage(int weaponDamage) const;

    unsigned int getLevel() const;

    void increaseExperience(unsigned int _experience);

    int modifyLife(int damage, unsigned int attackerLevel, unsigned int defense,
                   bool isAPlayer);

    int getMaxLife() const;

    int getCurrentLife() const;

    //Restaura hasta amount cantidad de vida, sin pasarse de la cantidad maxima
    void restoreLife(unsigned int amount);

    //Restaura hasta amount cantidad de mana, sin pasarse de la cantidad maxima
    void restoreMana(unsigned int amount);

    bool isDead() const;

private:
    void _increaseStats();
};


#endif //ARGENTUM_PLAYERSTATS_H
