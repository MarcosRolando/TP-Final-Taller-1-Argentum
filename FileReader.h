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
    FileReader(std::string path);
    void getClassModifiers(Modifiers& modifiers, std::string type);
    void getRaceModifiers(Modifiers& modifiers, std::string type);
    void getMonsterStats(MonsterStats& monsterStats, std::string type);

    void getGoldModifiers(GoldModifiers& goldModifiers);
    void getXPModifiers(XPModifiers& xpModifiers);

    float getCritAttackChance();
    float getDodgeChance();

    unsigned int getNewbieLevel();
    unsigned int getmaxLevelDif();

    unsigned int getInventorySize();
    ~FileReader();
};


#endif //ARGENTUM_FILEREADER_H
