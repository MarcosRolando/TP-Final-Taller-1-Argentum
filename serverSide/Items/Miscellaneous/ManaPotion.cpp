//
// Created by agustin on 19/6/20.
//

#include "ManaPotion.h"
#include "../../Entities/Player.h"

using namespace GameType;

ManaPotion::ManaPotion(): Potion(MANA_POTION) {

}

void ManaPotion::restoreStat(Player &player) {
    player.restoreMana(recoveryValue);
}

ManaPotion::~ManaPotion() = default;
