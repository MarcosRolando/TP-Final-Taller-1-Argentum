//
// Created by ivan on 10/6/20.
//

#ifndef ARGENTUM_CALCULATOR_H
#define ARGENTUM_CALCULATOR_H


class Calculator {
public:

    static int calculateMaxLife(unsigned int constitution, unsigned int classLifeMultiplier,
                                unsigned int raceLifeMultiplier, unsigned int level);

    static unsigned int calculateMaxMana(unsigned int intelligence, unsigned int classManaMultiplier,
                                        unsigned int raceManaMultiplier, unsigned int level);

    static unsigned int calculateGoldDrop(unsigned int maxLife);

    static unsigned int calculateMaxSafeGold(unsigned int level);

    static unsigned int calculateNextLevelXP(unsigned int level);

    static unsigned int calculateAttackXP(unsigned int dmg, unsigned int
    myLevel, unsigned int otherLevel);

    static unsigned int calculateKillXP(unsigned int myLevel, unsigned int otherLevel,
                                        unsigned int othermaxLife);

    static int calculateDamage(unsigned int strength, int weaponDamage);

    static bool canDodge(unsigned int agility);

    static int getRandomInt(int minRange, int maxRange);

    static bool isCritical();

    static int lifeRecovered(unsigned int recoveryRate, double timeStep);

    int manaRecoveredNoMeditation(double timeStep);

    int manaRecoveredWithMeditation(double timeStep);

private:
    static float _getRandomFloat(float minRange, float maxRange);
};


#endif //ARGENTUM_CALCULATOR_H
