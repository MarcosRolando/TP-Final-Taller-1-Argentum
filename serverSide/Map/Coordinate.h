//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_COORDINATE_H
#define ARGENTUM_COORDINATE_H

#include <functional>
#include <cstdlib>

//Struct auxiliar para facilitar el paso de coordenadas, debido a esto no
//tiene ningun comportamiento y sus atributos son publicos
struct Coordinate {
    int iPosition; //todo ver si lo cambiamos a int32 xq estamos mandando esto
    int jPosition;

    bool operator==(const Coordinate& other) {
        return ((iPosition == other.iPosition) && (jPosition == other.jPosition));
    }

    bool operator!=(const Coordinate& other) {
        return !((iPosition == other.iPosition) && (jPosition == other.jPosition));
    }

    unsigned int calculateDistance(const Coordinate& other) {
        return std::abs(iPosition - other.iPosition) + std::abs(jPosition - other.jPosition);
    }
};

namespace std {
    template <> struct hash<Coordinate> {
        size_t operator()(const Coordinate& x) const {
            return (x.jPosition << 15) + x.jPosition;
        }
    };

    template <> struct equal_to<Coordinate> {
        size_t operator()(const Coordinate& x, const Coordinate& y) const {
            return (x.iPosition == y.iPosition) && (x.jPosition == y.jPosition);
        }
    };
}

#endif //ARGENTUM_COORDINATE_H
