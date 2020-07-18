//
// Created by agustin on 3/7/20.
//

#ifndef ARGENTUM_USERETURNDATA_H
#define ARGENTUM_USERETURNDATA_H

#include "Item.h"

/*Este struct es util para cuando mandamos los updates a los players de lo que
 * se equipo otro jugador*/

struct UseReturnData {
    GameType::EquipmentPlace equipmentPlace;
    int32_t id;
};


#endif //ARGENTUM_USERETURNDATA_H
