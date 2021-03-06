//
// Created by agustin on 5/7/20.
//

#ifndef ARGENTUM_ITEMDATA_H
#define ARGENTUM_ITEMDATA_H

#include <cstdint>
#include "../../libs/GameEnums.h"
#include "../Map/Coordinate.h"

/*Este struct es util para encapsular los datos necesarios del item
 * para el protcolo*/

struct ItemData {
    GameType::ItemType type;
    int32_t id;
    Coordinate coordinate;
};

#endif //ARGENTUM_ITEMDATA_H
