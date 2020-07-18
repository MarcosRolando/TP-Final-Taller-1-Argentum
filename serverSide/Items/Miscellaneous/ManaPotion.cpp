//
// Created by agustin on 19/6/20.
//

#include "ManaPotion.h"
#include "../../Entities/Player.h"

void ManaPotion::restoreStat(Player &player) {
    player.restoreMana(recoveryValue);
}

ManaPotion::~ManaPotion() = default;
