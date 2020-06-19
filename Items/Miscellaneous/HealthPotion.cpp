//
// Created by agustin on 19/6/20.
//

#include "HealthPotion.h"

using namespace Config;

HealthPotion::HealthPotion(): Potion(Configuration::getInstance().configPotionData(HEALTH_POTION)) {

}

void HealthPotion::restoreStat(Player &player) {
    player.restoreLife(recoveryValue);
}
