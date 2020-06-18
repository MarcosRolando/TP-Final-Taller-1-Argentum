//
// Created by ivan on 8/6/20.
//

#ifndef ARGENTUM_CONFIGFILEREADER_H
#define ARGENTUM_CONFIGFILEREADER_H

#include <fstream>
#include "jsoncpp/json/json.h"
#include "Configuration.h"
#include <unordered_map>

enum Race {HUMAN, ELF, DWARF, GNOME};

enum Class {WIZARD, CLERIC, PALADIN, WARRIOR};

enum Monster {SKELETON, ZOMBIE, SPIDER, GOBLIN};

enum Weapon {LONGSWORD, AXE, WARHAMMER, ASH_ROD, ELVEN_FLUTE, LINKED_STAFF,
    SIMPLE_BOW, COMPOUND_BOW, GNARLED_STAFF};

enum Clothing {COMMON_CLOTHING, LEATHER_ARMOR, PLATE_ARMOR, BLUE_TUNIC, HOOD,
    IRON_HELMET, TURTLE_SHIELD, IRON_SHIELD, MAGIC_HAT};

struct Modifiers {
    unsigned int health;
    unsigned int mana;
    unsigned int constitution;
    unsigned int intelligence;
    unsigned int agility;
    unsigned int strength;
    unsigned int meditationRate;
    unsigned int recoveryRate;
};

struct WeaponStats {
    unsigned int minDmg;
    unsigned int maxDmg;
    unsigned int manaConsumption;
    unsigned int range;
};

struct ClothingStats {
    unsigned int minDefense;
    unsigned int maxDefense;
};

struct MonsterStats {
    int health;
    unsigned int damage;
    unsigned int rangeOfVision;
    unsigned int minLevel;
    unsigned int maxLevel;
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
    std::unordered_map<std::string, Class> classes;
    std::unordered_map<std::string, Race> races;
    std::unordered_map<std::string, Monster> monsters;
    std::unordered_map<std::string, Weapon> weapons;
    std::unordered_map<std::string, Clothing> clothing;

public:
    ConfigFileReader(const std::string& path);

    void loadClassModifiers(std::unordered_map<Class, Modifiers>& mods);
    void loadRaceModifiers(std::unordered_map<Race, Modifiers>& mods);
    void loadMonsterStats(std::unordered_map<Monster, MonsterStats>& stats);

    void loadWeaponStats(std::unordered_map<Weapon, WeaponStats>& stats);
    void loadClothingStats(std::unordered_map<Clothing, ClothingStats>& stats);

    void loadGoldModifiers(GoldModifiers& goldModifiers);
    void loadXPModifiers(XPModifiers& xpModifiers);

    float loadCritAttackChance();
    float loadDodgeChance();

    unsigned int loadNewbieLevel();
    unsigned int loadmaxLevelDif();

    unsigned int loadPlayerVisionRange();

    ~ConfigFileReader();

private:
    static void _getModifiers(Modifiers &modifier, Json::Value& currModifier);
    static void _getMonsterStats(MonsterStats &stats, Json::Value &currMonster);

    static void _getWeaponStats(WeaponStats &stats, Json::Value& currWeapon);

    static void _getClothingStats(ClothingStats &stats, Json::Value& currClothing);
};


#endif //ARGENTUM_CONFIGFILEREADER_H
