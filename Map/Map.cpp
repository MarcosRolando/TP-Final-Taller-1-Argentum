//
// Created by agustin on 7/6/20.
//

#include <queue>
#include "Map.h"

//////////////////////////////PRIVATE/////////////////////////////



int Map::_inverseCoordinateDistance(const PrivatePointAndDistance p) {
    return -p.distance;
}

void Map::_buildSearchRegion(Coordinate center, unsigned int range, Coordinate& topRight, Coordinate& bottomLeft) const {
    Coordinate aux;
    aux.iPosition = center.iPosition - range;
    aux.jPosition = center.jPosition - range;
    topRight = _getValidCoordinate(aux);
    aux.iPosition = center.iPosition + range;
    aux.jPosition = center.jPosition + range;
    bottomLeft = _getValidCoordinate(aux);
}

Coordinate Map::_getValidCoordinate(Coordinate coordinate) const {
    if (coordinate.jPosition >= tiles[0].size()) {
        coordinate.jPosition = tiles[0].size() - 1;
    } else if (coordinate.jPosition < 0) {
        coordinate.jPosition = 0;
    }
    if (coordinate.jPosition >= tiles.size()) {
        coordinate.iPosition = tiles.size() - 1;
    } else if (coordinate.iPosition < 0) {
        coordinate.iPosition = 0;
    }
    return coordinate;
}


//////////////////////////////PUBLIC/////////////////////////////


unsigned int Map::attackTile(unsigned int damage, unsigned int level,
                             Coordinate coordinate) {
    return tiles[coordinate.iPosition][coordinate.jPosition].attacked(damage, level);
}

void Map::getTargets(Coordinate center, unsigned int range, std::vector<Coordinate>& targets) const {
    Coordinate topRight;
    Coordinate bottomLeft;
    Coordinate aux;
    _buildSearchRegion(center, range, topRight, bottomLeft);
    for (int i = topRight.iPosition; i < bottomLeft.iPosition; ++i) {
        for (int j = topRight.jPosition; j < bottomLeft.jPosition; ++j) {
            if (tiles[i][j].hasMonsterTarget()) {
                aux.iPosition = i;
                aux.jPosition = j;
                targets.push_back(aux);
            }
        }
    }
}

void Map::getPath(Coordinate currentPosition, Coordinate desiredPosition, std::list<Coordinate>& path) const {
    std::priority_queue<Coordinate> nodes(&_inverseCoordinateDistance);
    nodes.push(currentPosition);
    while (!nodes.empty()) {

    }
}
