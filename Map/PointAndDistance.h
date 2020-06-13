//
// Created by agustin on 10/6/20.
//

#ifndef ARGENTUM_POINTANDDISTANCE_H
#define ARGENTUM_POINTANDDISTANCE_H

#include "Coordinate.h"

//Este struct es auxiliar, solo deberia ser usado por el mapa para pathfinding,
//se declara en el header por tener que declarar la funcion privada
struct PointAndDistance {
    Coordinate point;
    unsigned int distance;
};


#endif //ARGENTUM_POINTANDDISTANCE_H
