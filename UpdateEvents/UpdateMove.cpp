//
// Created by marcos on 6/29/20.
//

#include "UpdateMove.h"
#include "../Map/Map.h"

void UpdateMove::operator()() {
    map.moveEntity(nickname, direction, distanceTravelled, reachedDestination);
}
