//
// Created by agustin on 14/6/20.
//

#ifndef ARGENTUM_PLAYERSTATS_H
#define ARGENTUM_PLAYERSTATS_H

#include "../Config/GameEnums.h"

class EntityTests;
class MapTests;

class PlayerStats {
private:
    bool isMeditating;
    double timeElapsed;

    unsigned int constitution;
    unsigned int intelligence;
    unsigned int agility;
    unsigned int strength;

    unsigned int classLifeMultiplier;
    unsigned int raceLifeMultiplier;
    unsigned int classManaMultiplier;
    unsigned int raceManaMultiplier;
    unsigned int recoveryRate;
    unsigned int meditationRate;

    unsigned int experience;
    unsigned int nextLevelExperience;
    unsigned int level;
    unsigned int currentMana;
    int currentLife;
    unsigned int maxMana;
    int maxLife;

    friend EntityTests;
    friend MapTests;

public:
    PlayerStats(GameType::Race _race, GameType::Class _class, unsigned int _level, unsigned int _experience);

    //Retorna el danio base que logro hacer el arma del player para el ataque
    int getTotalDamage(int weaponDamage) const;

    //Retorna el level actual del player
    unsigned int getLevel() const;

    //Aumenta el xp del player
    void increaseExperience(unsigned int _experience);

    //Modifica la vida del player acorde al danio/curacion ocasionados
    int modifyLife(int damage, unsigned int attackerLevel, unsigned int defense,
                   bool isAPlayer);

    //Retorna la maxima vida que puede tener el player dado su nivel actual
    int getMaxLife() const;

    //Retorna la vida actual del player
    int getCurrentLife() const;

    //Restaura hasta amount cantidad de vida, sin pasarse de la cantidad maxima
    void restoreLife(unsigned int amount);

    //Restaura hasta amount cantidad de mana, sin pasarse de la cantidad maxima
    void restoreMana(unsigned int amount);

    //Retorna si el player esta o no muerto
    bool isDead() const;

    //Actualiza el estado de la vida y el mana del player
    void update(double timeStep);

    //Setea el player a modo meditacion
    void startMeditating();

    //Hace que el player deje de estar en modo meditacion
    void stopMeditating();

    unsigned int &getCurrentMana();

private:
    void _increaseStats();
};


#endif //ARGENTUM_PLAYERSTATS_H
