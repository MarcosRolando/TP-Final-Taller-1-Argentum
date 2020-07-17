//
// Created by ivan on 8/6/20.
//

#ifndef ARGENTUM_CONFIGURATION_H
#define ARGENTUM_CONFIGURATION_H

#include "ConfigFileReader.h"
#include <unordered_map>

/*La siguiente clase toma los valores que lee el ConfigFileReader y los guarda en memoria para que el resto del
 * juego pueda acceder a ellos rapidamente*/

class Configuration {

private:
    std::unordered_map<GameType::Race, Config::Modifiers> raceModifiers{};
    std::unordered_map<GameType::Class, Config::Modifiers> classModifiers{};
    std::unordered_map<GameType::Entity, Config::MonsterStats> monsterStats{};
    std::unordered_map<GameType::Weapon, Config::WeaponData> weaponData{};
    std::unordered_map<GameType::Clothing, Config::ClothingData> clothingData{};
    std::unordered_map<GameType::Potion, Config::PotionData> potionData{};

    Config::GoldModifiers goldModifiers{};

    Config::XPModifiers xpModifiers{};

    float criticalAttackChance;
    float dodgeChance;

    unsigned int newbieLevel;
    unsigned int maxLevelDif;

    unsigned int timeBetweenMonsterSpawns{};
    unsigned int monsterSpawnAmount{};
    unsigned int maxMonsterAmount{};

    unsigned int initialMerchantGold;
    std::string goldName;

    unsigned int playerSpeed;

public:
    Configuration(Configuration const&) = delete;
    void operator=(Configuration const&) = delete;

    /*Retorna la instancia Singleton del Configuration*/
    static Configuration& getInstance();

    /*Retorna los modificadores de clase*/
    const Config::Modifiers& configClassModifiers(GameType::Class _class) const;

    /*Retorna los modificadores de clase*/
    const Config::Modifiers& configRaceModifiers(GameType::Race race) const;

    /*Retorna los modificadores de clase*/
    const Config::MonsterStats& configMonsterStats(GameType::Entity monster) const;

    /*Retorna los modificadores de clase*/
    const Config::WeaponData& configWeaponData(GameType::Weapon weapon) const;

    /*Retorna los modificadores de clase*/
    const Config::ClothingData& configClothingData(GameType::Clothing clothes) const;

    /*Retorna los modificadores de clase*/
    const Config::PotionData& configPotionData(GameType::Potion potion) const;

    /*Retorna los modificadores de clase*/
    const Config::GoldModifiers& configGoldModifiers() const;

    /*Retorna los modificadores de clase*/
    const Config::XPModifiers& configXPModifiers() const;

    /*Retorna los modificadores de clase*/
    const std::unordered_map<GameType::Weapon, Config::WeaponData>& configAllWeaponsData();

    /*Retorna los modificadores de clase*/
    const std::unordered_map<GameType::Clothing, Config::ClothingData>& configAllClothingData();

    /*Retorna los modificadores de clase*/
    const std::unordered_map<GameType::Potion, Config::PotionData>& configAllPotionsData();

    /*Retorna la probabilidad de un ataque critico*/
    float configCriticalAttackChance() const;

    /*Retorna un coeficiente que afecta la probabilidad de esquivar un ataque*/
    float configDodgeChance() const;

    /*Retorna el newbie level*/
    unsigned int configNewbieLevel() const;

    /*Retorna la maxima diferencia que puede haber entre 2 players para que puedan atacarse*/
    unsigned int configMaxLevelDif() const;

    /*Retorna el tiempo entre spawns de monstruos*/
    unsigned int configTimeBetweenMonsterSpawns() const;

    /*Retorna la maxima cantidad de monstruos que puede haber en simultaneo vivos en la partida*/
    unsigned int configMaxMonsterAmount() const;

    /*Retorna la cantidad de monstruos que spawnean a la vez en cada spawn*/
    unsigned int configMonsterSpawnAmount() const;

    /*Retorna la cantidad inicial de oro de los mercaderes*/
    unsigned int configInitialMerchantGold() const;

    /*Retorna el nombre a mostrar del oro (mostramos Gold pero podria ponerse un nombre mas tuneado*/
    const std::string &configGetGoldName() const;

    /*Retorna la velocidad del player para moverse*/
    unsigned int configPlayerSpeed() const;

private:
    Configuration();
};


#endif //ARGENTUM_CONFIGURATION_H
