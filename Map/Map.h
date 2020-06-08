//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H

#include <vector>
#include "Tile.h"
#include "Coordinate.h"

class Map {
private:
    std::vector<std::vector<Tile>> tiles;

public:
    //Ataca la tile y retorna cuanto danio le hizo al entity guardado, si no
    //hay un etity revuelve 0
    unsigned int attackTile(unsigned int damage, Coordinate coordinate);
};


#endif //ARGENTUM_MAP_H
