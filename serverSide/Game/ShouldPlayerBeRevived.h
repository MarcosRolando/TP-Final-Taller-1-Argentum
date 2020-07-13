//
// Created by agustin on 8/7/20.
//

#ifndef ARGENTUM_SHOULDPLAYERBEREVIVED_H
#define ARGENTUM_SHOULDPLAYERBEREVIVED_H

#include <sstream>
#include "../Map/Coordinate.h"

struct ResurrectData;
class Map;

class ShouldPlayerBeRevived {
private:
    Map& map;
    std::stringstream& data;
    double timeStep;

private:
    void _storeResurrectMessage(const ResurrectData& resurrectData);
    void _storeTeleportMessage(const ResurrectData& resurrectData, Coordinate newPosition);

public:
    explicit ShouldPlayerBeRevived(Map& map, std::stringstream& data, double timeStep);

    bool operator()(ResurrectData& resurrectData);
};


#endif //ARGENTUM_SHOULDPLAYERBEREVIVED_H
