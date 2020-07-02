//
// Created by marcos on 7/2/20.
//

#ifndef ARGENTUM_GUIPLAYERINFO_H
#define ARGENTUM_GUIPLAYERINFO_H

#include "../../Map/Coordinate.h"

struct GUIPlayerInfo {
    int32_t totalHealth, totalMana, nextLevelXP;
    int32_t health, mana, xp;
    int32_t level;
    int32_t constitution, strength, agility, intelligence;
    int32_t gold;
    Coordinate position;
};
enum EquippedItems {
    Helmet,
    Armor,
    Weapon,
    Shield,
};

#endif //ARGENTUM_GUIPLAYERINFO_H
