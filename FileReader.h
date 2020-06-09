//
// Created by ivan on 8/6/20.
//

#ifndef ARGENTUM_FILEREADER_H
#define ARGENTUM_FILEREADER_H

#include <fstream>
#include <vector>

#include "jsoncpp/json/json.h"
#include "Configuration.h"

struct Modifiers;
struct MonsterStats;
struct GoldModifiers;
struct XPModifiers;


class FileReader {
private:
    Json::Reader reader;
    Json::Value obj;
    std::ifstream file;

public:
    FileReader(const std::string& path);

    void getClassModifiers(Modifiers& modifiers, const std::string& type);
    void getRaceModifiers(Modifiers& modifiers, const std::string& type);
    void getMonsterStats(MonsterStats& monsterStats, const std::string& type);

    void getGoldModifiers(GoldModifiers& goldModifiers);
    void getXPModifiers(XPModifiers& xpModifiers);

    float getCritAttackChance();
    float getDodgeChance();

    unsigned int getNewbieLevel();
    unsigned int getmaxLevelDif();

    unsigned int getInventorySize();
    unsigned int getPlayerVisionRange();

    ~FileReader();

private:
    void _getModifiers(Modifiers &modifier, Json::Value& currModifier);
    void _getStats(MonsterStats &stats, Json::Value &currStat);
};


#endif //ARGENTUM_FILEREADER_H
