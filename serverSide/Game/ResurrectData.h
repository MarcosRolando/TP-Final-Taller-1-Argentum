//
// Created by agustin on 8/7/20.
//

#ifndef ARGENTUM_RESURRECTDATA_H
#define ARGENTUM_RESURRECTDATA_H

#include "../Map/Coordinate.h"

class Player;

//struct auxiliar para guardar la informacion de un player que sera resucitado
struct ResurrectData {
    double timeToWait;
    double timeWaited;
    Coordinate resurrectingPriest;
    Player* playerToResurrect;
};

#endif //ARGENTUM_RESURRECTDATA_H
