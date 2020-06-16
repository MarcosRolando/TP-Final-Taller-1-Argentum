//
// Created by ivan on 8/6/20.
//

#ifndef ARGENTUM_CONFIGFILEREADER_H
#define ARGENTUM_CONFIGFILEREADER_H

#include <fstream>
#include "jsoncpp/json/json.h"
#include "Configuration.h"
#include <unordered_map>

struct Modifiers;
struct MonsterStats;
struct WeaponStats;
struct ClothingStats;
struct GoldModifiers;
struct XPModifiers;



class ConfigFileReader {
private:
    Json::Reader reader;
    Json::Value obj;
    std::ifstream file;

public:
    ConfigFileReader(const std::string& path);

    void loadClassModifiers(std::vector<Modifiers>& mods);
    void loadRaceModifiers(std::vector<Modifiers>& mods);
    void loadMonsterStats(std::vector<MonsterStats>& stats);

    void loadWeaponStats(std::vector<WeaponStats>& stats);
    void loadClothingStats(std::vector<ClothingStats>& stats);

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

    static void _getWeaponStats(WeaponStats &stats, Json::Value currWeapon);

    static void _getClothingStats(ClothingStats &stats, Json::Value currClothing);
};


#endif //ARGENTUM_CONFIGFILEREADER_H
