//
// Created by agustin on 19/6/20.
//

#include "HealthPotion.h"
#include "../../Entities/Player.h"

using namespace GameType;

HealthPotion::HealthPotion(): Potion(HEALTH_POTION) {

}

void HealthPotion::restoreStat(Player &player) {
    player.restoreLife(recoveryValue);
}

HealthPotion::~HealthPotion() = default;
