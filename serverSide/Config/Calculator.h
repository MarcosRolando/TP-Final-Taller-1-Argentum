//
// Created by ivan on 10/6/20.
//

#ifndef ARGENTUM_CALCULATOR_H
#define ARGENTUM_CALCULATOR_H


class Calculator {
public:

    /*Calcula la cantidad maxima de vida del player*/
    static int calculateMaxLife(unsigned int constitution, unsigned int classLifeMultiplier,
                                unsigned int raceLifeMultiplier, unsigned int level);

    /*Calcula la cantidad maxima de mana del player*/
    static unsigned int calculateMaxMana(unsigned int intelligence, unsigned int classManaMultiplier,
                                        unsigned int raceManaMultiplier, unsigned int level);

    /*Calcula el drop de oro dropeado por un monstruo al matarlo*/
    static unsigned int calculateGoldDrop(unsigned int maxLife);

    /*Calcula cantidad de oro en mano segura*/
    static unsigned int calculateMaxSafeGold(unsigned int level);

    /*Calcula el XP necesario para subir de nivel*/
    static unsigned int calculateNextLevelXP(unsigned int level);

    /*Calcula el XP ganado en el ataque*/
    static unsigned int calculateAttackXP(int dmg, unsigned int
                                                        myLevel, unsigned int otherLevel);

    /*Calcula la cantidad de XP ganada por el player al matar a otro NPC (player o monster*/
    static unsigned int calculateKillXP(unsigned int myLevel, unsigned int otherLevel,
                                        unsigned int othermaxLife);

    /*Calcula el danio inicial del player, este danio podra ser esquivado o disminuido en base a la defensa del rival*/
    static int calculateDamage(unsigned int strength, int weaponDamage);

    /*Retorna si el npc o player pudo o no esquivar el ataque*/
    static bool canDodge(unsigned int agility);

    /*Retorna un int random entre minRage y maxRange*/
    static int getRandomInt(int minRange, int maxRange);

    /*Retorna true si el ataque fue critical, flase en caso contrario*/
    static bool isCritical();

    /*Retorna la cantidad de vida recupera en base al recovery rate del player y el tiempo pasado*/
    static int lifeRecovered(unsigned int recoveryRate, double timeElpased);

    /*Retorna la cantidad de mana recuperada sin estar en estado de meditacion en base al tiempo pasado*/
    static unsigned int manaRecoveredNoMeditation(unsigned int recoveryRate, double timeElpased);

    /*Retorna la cantidad de mana recuperado cuando se esta en estado de meditacion en base al tiempo pasado*/
    static unsigned int manaRecoveredWithMeditation(unsigned int meditationRate,
                                           unsigned int intelligence, double timeElpased);

private:
    static float _getRandomFloat(float minRange, float maxRange);
};


#endif //ARGENTUM_CALCULATOR_H
