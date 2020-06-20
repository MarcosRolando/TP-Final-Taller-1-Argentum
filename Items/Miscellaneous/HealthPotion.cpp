//
// Created by agustin on 19/6/20.
//

#include "HealthPotion.h"
#include "../../Entities/Player.h"

using namespace GameType;

/*
class Player {
public:
    void restoreLife(unsigned int amount);
};
*/

HealthPotion::HealthPotion(): Potion(Configuration::getInstance().configPotionData(HEALTH_POTION)) {

}

void HealthPotion::restoreStat(Player &player) {
    player.restoreLife(recoveryValue);
}
