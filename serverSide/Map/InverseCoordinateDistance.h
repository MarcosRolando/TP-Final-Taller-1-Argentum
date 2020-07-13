//
// Created by agustin on 10/6/20.
//

#ifndef ARGENTUM_INVERSECOORDINATEDISTANCE_H
#define ARGENTUM_INVERSECOORDINATEDISTANCE_H


#include "PointAndDistance.h"

//Functor utilizado para obtener el nodo de menor distancia en la priority_queue
//para el pathfinding
class InverseCoordinateDistance {
public:
    bool operator()(const PointAndDistance& a, const PointAndDistance& b);
};


#endif //ARGENTUM_INVERSECOORDINATEDISTANCE_H
