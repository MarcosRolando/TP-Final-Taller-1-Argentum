//
// Created by ivan on 8/6/20.
//

#ifndef ARGENTUM_CONFIGFILEREADER_H
#define ARGENTUM_CONFIGFILEREADER_H

#include <fstream>
#include <unordered_map>
#include "../../libs/GameEnums.h"
#include "json.hpp"

namespace Config {

    struct Modifiers {
        unsigned int lifeMultiplier;
        unsigned int manaMultiplier;
        unsigned int constitution;
        unsigned int intelligence;
        unsigned int agility;
        unsigned int strength;
        unsigned int meditationRate;
        unsigned int recoveryRate;
    };

    struct WeaponData {
        std::string name;
        int minDmg;
        int maxDmg;
        unsigned int manaConsumption;
        unsigned int range;
        unsigned int price;
    };

    struct ClothingData {
        std::string name;
        unsigned int minDefense;
        unsigned int maxDefense;
        unsigned int price;
    };

    struct MonsterStats {
        int life;
        unsigned int damage;
        unsigned int constitution;
        unsigned int agility;
        unsigned int strength;
        unsigned int rangeOfVision;
        unsigned int minLevel;
        unsigned int maxLevel;
        unsigned int reactionSpeed;
        unsigned int speed;
    };

    struct PotionData {
        std::string name;
        unsigned int recoveryValue;
        unsigned int price;
    };

    struct GoldModifiers {
        float goldDropFactorMin;
        float goldDropFactorMax;
        unsigned int safeGoldFactor;
        float safeGoldLevelModifier;
    };

    struct XPModifiers {
        unsigned int nextLevelFactor;
        float nextLevelModifier;
        unsigned int attackXPModifier;
        unsigned int killXPModifier;
        float killXPMinRange;
        float killXPMaxRange;
    };

    /*La clase ConfigFileReader es la encargada de parsear el archivo de configuracion de json que contiene los datos
     * tuneables del juego*/

    class ConfigFileReader {
    private:
        nlohmann::json obj;
        std::unordered_map<std::string, GameType::Class> classes;
        std::unordered_map<std::string, GameType::Race> races;
        std::unordered_map<std::string, GameType::Entity> monsters;
        std::unordered_map<std::string, GameType::Weapon> weapons;
        std::unordered_map<std::string, GameType::Clothing> clothing;
        std::unordered_map<std::string, GameType::Potion> potions;

    public:
        explicit ConfigFileReader(const std::string &path);

        /*Carga los modificadores de las clases*/
        void loadClassModifiers(std::unordered_map<GameType::Class, Modifiers> &mods);

        /*Carga los modificadores de las razas*/
        void loadRaceModifiers(std::unordered_map<GameType::Race, Modifiers> &mods);

        /*Carga los stats de los monsters*/
        void loadMonsterStats(std::unordered_map<GameType::Entity, MonsterStats> &stats);

        /*Carga los datos de las armas*/
        void loadWeaponData(std::unordered_map<GameType::Weapon, WeaponData> &stats);

        /*Carga los datos de la ropa*/
        void loadClothingData(std::unordered_map<GameType::Clothing, ClothingData> &stats);

        /*Carga los modificadores del oro*/
        void loadGoldModifiers(GoldModifiers &goldModifiers);

        /*Carga los modificadores de la XP*/
        void loadXPModifiers(XPModifiers &xpModifiers);

        /*Carga la probabilidad de ataque critico*/
        float loadCritAttackChance();

        /*Carga la probabilidad de esquivar un ataque*/
        float loadDodgeChance();

        /*Carga el nivel de newbie de player*/
        unsigned int loadNewbieLevel();

        /*Carga la maxima diferencia de nivel permitida para el ataque entre players*/
        unsigned int loadmaxLevelDif();

        /*Carga la velocidad de los players para caminar*/
        unsigned int loadPlayerSpeed();

        /*Carga la data de las pociones (vida/mana recuperado)*/
        void loadPotionData(std::unordered_map<GameType::Potion, PotionData>& stats);

        /*Carga la data de spawn de los monsters (cada cuanto respawnean, cantidad que respawnean, etc)*/
        void loadMonsterSpawnData(unsigned int &maxMonsterAmount,
                                  unsigned int &timeBetweenMonsterSpawns,
                                  unsigned int &monsterSpawnAmount);

        /*Carga el oro incial que tienen los mercaderes (para comprar items de los players)*/
        unsigned int loadInitialMerchantGold();

        /*Carga el tiempo (en segundos) que debe pasar para que el player recupere vida/mana*/
        double loadTimeForPlayerRecovery();

    private:
        static void
        _getModifiers(Modifiers &modifier, nlohmann::json &currModifier);

        static void
        _getMonsterStats(MonsterStats &stats, nlohmann::json &currMonster);

        static void
        _getWeaponData(WeaponData &stats, nlohmann::json &currWeapon);

        static void
        _getClothingData(ClothingData &stats, nlohmann::json &currClothing);

        static void _getPotionData(PotionData &stats, nlohmann::json &currPotion);
    };
}

#endif //ARGENTUM_CONFIGFILEREADER_H
