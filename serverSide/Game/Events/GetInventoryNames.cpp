//
// Created by agustin on 13/7/20.
//

#include "GetInventoryNames.h"

#include "../../Entities/Player.h"

GetInventoryNames::GetInventoryNames(Player &player): player(player) {

}

void GetInventoryNames::operator()(ServerProtocol &protocol) {
    player.getInventoryNames();
}
