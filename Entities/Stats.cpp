//
// Created by agustin on 14/6/20.
//

#include "Stats.h"
#include <ctime>
#include "../Config/Calculator.h"

using namespace Config;

Stats::Stats(Race _race, Class _class, unsigned int _level, unsigned int _experience) {
    Configuration& config = Configuration::getInstance();
    Modifiers classModifier = config.configClassModifiers(_class);
    Modifiers raceModifier = config.configRaceModifiers(_race);
    classLifeMultiplier = classModifier.lifeMultiplier;
    classManaMultiplier = classModifier.manaMultiplier;
    raceLifeMultiplier = raceModifier.lifeMultiplier;
    raceManaMultiplier = raceModifier.manaMultiplier;
    constitution = classModifier.constitution + raceModifier.constitution;
    intelligence = classModifier.intelligence + raceModifier.intelligence;
    agility = classModifier.agility + raceModifier.agility;
    strength = classModifier.strength + raceModifier.strength;
    isMeditating = false;
    generalTimer = time(nullptr);
    meditationTimer = generalTimer;
    experience = _experience;
    level = _level;
    maxLife = Calculator::calculateMaxLife(classModifier, raceModifier, level);
    maxMana = Calculator::calculateMaxMana(classModifier, raceModifier, level);
    currentLife = maxLife;
    currentMana = maxMana;
}
