//
// Created by ivan on 8/6/20.
//

#ifndef ARGENTUM_CONFIGFILEREADER_H
#define ARGENTUM_CONFIGFILEREADER_H

#include <fstream>
#include "jsoncpp/json/json.h"
#include <unordered_map>
#include "../../libs/GameEnums.h"

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

    class ConfigFileReader {
    private:
        Json::Reader reader;
        Json::Value obj;
        std::ifstream file;
        std::unordered_map<std::string, GameType::Class> classes;
        std::unordered_map<std::string, GameType::Race> races;
        std::unordered_map<std::string, GameType::Entity> monsters;
        std::unordered_map<std::string, GameType::Weapon> weapons;
        std::unordered_map<std::string, GameType::Clothing> clothing;
        std::unordered_map<std::string, GameType::Potion> potions;

    public:
        explicit ConfigFileReader(const std::string &path);

        void loadClassModifiers(std::unordered_map<GameType::Class, Modifiers> &mods);

        void loadRaceModifiers(std::unordered_map<GameType::Race, Modifiers> &mods);

        void loadMonsterStats(std::unordered_map<GameType::Entity, MonsterStats> &stats);

        void loadWeaponData(std::unordered_map<GameType::Weapon, WeaponData> &stats);

        void loadClothingData(std::unordered_map<GameType::Clothing, ClothingData> &stats);

        void loadGoldModifiers(GoldModifiers &goldModifiers);

        void loadXPModifiers(XPModifiers &xpModifiers);

        float loadCritAttackChance();

        float loadDodgeChance();

        unsigned int loadNewbieLevel();

        unsigned int loadmaxLevelDif();

        unsigned int loadPlayerVisionRange();

        unsigned int loadPlayerSpeed();

        void loadPotionData(std::unordered_map<GameType::Potion, PotionData>& stats);

        ~ConfigFileReader();

        void loadMonsterSpawnData(unsigned int &maxMonsterAmount,
                                  unsigned int &timeBetweenMonsterSpawns,
                                  unsigned int &monsterSpawnAmount);

        unsigned int loadInitialMerchantGold();

    private:
        static void
        _getModifiers(Modifiers &modifier, Json::Value &currModifier);

        static void
        _getMonsterStats(MonsterStats &stats, Json::Value &currMonster);

        static void
        _getWeaponData(WeaponData &stats, Json::Value &currWeapon);

        static void
        _getClothingData(ClothingData &stats, Json::Value &currClothing);

        static void _getPotionData(PotionData &stats, Json::Value &currPotion);
    };
}

#endif //ARGENTUM_CONFIGFILEREADER_H
