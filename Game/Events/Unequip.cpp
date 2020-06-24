//
// Created by agustin on 23/6/20.
//

#include "Unequip.h"
#include "../../Entities/Player.h"

Unequip::Unequip(Player &player, EquipmentPlace _equipment): player(player) {
    equipment = _equipment;
}

Unequip::Unequip(Player &player): player(player) {
    equipment = EQUIPMENT_PLACE_WEAPON;
}

void Unequip::operator()() {
    if (equipment == EQUIPMENT_PLACE_WEAPON) {
        player.unequip();
    } else {
        player.unequip(equipment);
    }
}
