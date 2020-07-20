//
// Created by marcos on 6/27/20.
//

#ifndef ARGENTUM_COORDINATE_H
#define ARGENTUM_COORDINATE_H

struct Coordinate {
    int i;
    int j;

    bool operator!=(Coordinate& other) {
        return (i != other.i || j != other.j);
    }
};

#endif //ARGENTUM_COORDINATE_H
