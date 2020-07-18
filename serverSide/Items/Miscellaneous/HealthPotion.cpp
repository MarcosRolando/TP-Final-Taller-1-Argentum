//
// Created by agustin on 19/6/20.
//

#include "HealthPotion.h"
#include "../../Entities/Player.h"

void HealthPotion::restoreStat(Player &player) {
    player.restoreLife(recoveryValue);
}

HealthPotion::~HealthPotion() = default;
