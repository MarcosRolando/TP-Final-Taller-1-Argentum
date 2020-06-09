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

private:
    Coordinate _getValidCoordinate(Coordinate coordinate);
    void _buildSearchRegion(Coordinate center, unsigned int range, Coordinate& topRight, Coordinate& bottomLeft);
public:
    //Ataca la tile y retorna cuanto danio le hizo al entity guardado, si no
    //hay un etity revuelve 0
    unsigned int attackTile(unsigned int damage, unsigned int level,
                            Coordinate coordinate);

    //Almacena en el vector la cantidad de targets de un monstruo en un cuadrado centrado en
    //center de lado 2*range+1
    void getTargets(Coordinate center, unsigned int range, std::vector<Coordinate>& targets);

    //Retorna la posicion a la que se debera mover quien la llame para seguir el camino
    //mas corto hacia desiredPosition
    Coordinate getNextPosition(Coordinate currentPosition, Coordinate desiredPosition);
};


#endif //ARGENTUM_MAP_H
