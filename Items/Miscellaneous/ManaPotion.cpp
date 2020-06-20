//
// Created by agustin on 19/6/20.
//

#include "ManaPotion.h"

using namespace Config;

/*
class Player {
public:
    void restoreMana(unsigned int amount);
};
*/

ManaPotion::ManaPotion(): Potion(Configuration::getInstance().configPotionData(MANA_POTION)) {

}

void ManaPotion::restoreStat(Player &player) {
    player.restoreMana(recoveryValue);
}
