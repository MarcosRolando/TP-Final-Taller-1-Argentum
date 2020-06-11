//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H

#include <vector>
#include <list>
#include "Tile.h"
#include "Coordinate.h"


class Map {
private:
    std::vector<std::vector<Tile>> tiles;

private:
    bool _isCoordinateValid(Coordinate coordinate);
    Coordinate _getValidCoordinate(Coordinate coordinate) const;
    void _buildSearchRegion(Coordinate center, unsigned int range, Coordinate& topRight, Coordinate& bottomLeft) const;
    static bool _areCoordinatesEqual(Coordinate a, Coordinate b);
public:
    //Ataca la tile y retorna cuanto danio le hizo al entity guardado, si no
    //hay un etity revuelve 0
    unsigned int attackTile(unsigned int damage, unsigned int level,
                            Coordinate coordinate);

    //Almacena en el vector la cantidad de targets de un monstruo en un cuadrado centrado en
    //center de lado 2*range+1
    void getTargets(Coordinate center, unsigned int range, std::vector<Coordinate>& targets) const;

    //Almacena en el vector el camino que se debe seguir para llegar a la coordenada deseada
    void getPath(Coordinate currentPosition, Coordinate desiredPosition, std::list<Coordinate>& path) const;

    //Agrega el item al tile que se encuentra en la coordenada recibida, si la coordenada es invalida
    //tira invalid_argument
    void addItem(Coordinate position, std::shared_ptr<Item>&& item);
};


#endif //ARGENTUM_MAP_H
