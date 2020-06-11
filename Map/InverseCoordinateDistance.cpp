//
// Created by agustin on 10/6/20.
//

#include "InverseCoordinateDistance.h"

bool InverseCoordinateDistance::operator()(const PrivatePointAndDistance &a,
                                           const PrivatePointAndDistance &b) {
    return a.distance > b.distance;
}
