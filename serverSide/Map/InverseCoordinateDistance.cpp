//
// Created by agustin on 10/6/20.
//

#include "InverseCoordinateDistance.h"

bool InverseCoordinateDistance::operator()(const PointAndDistance &a,
                                           const PointAndDistance &b) {
    return a.distance > b.distance;
}
