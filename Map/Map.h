//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H

#include <vector>
#include <list>
#include "Tile.h"
#include "Coordinate.h"

//Este struct es auxiliar, solo deberia ser usado por el mapa, se declara en el
//header por tener que declarar la funcion privada
struct PrivatePointAndDistance {
    Coordinate point;
    int distance;
};

class Map {
private:
    std::vector<std::vector<Tile>> tiles;

private:
    Coordinate _getValidCoordinate(Coordinate coordinate) const;
    void _buildSearchRegion(Coordinate center, unsigned int range, Coordinate& topRight, Coordinate& bottomLeft) const;
    static int _inverseCoordinateDistance(const PrivatePointAndDistance p);
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
};


#endif //ARGENTUM_MAP_H
