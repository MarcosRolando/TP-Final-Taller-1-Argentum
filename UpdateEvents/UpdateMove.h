//
// Created by marcos on 6/29/20.
//

#ifndef ARGENTUM_UPDATEMOVE_H
#define ARGENTUM_UPDATEMOVE_H

#include "UpdateEvent.h"
#include <string>
#include "../Shared/GameEnums.h"

class Map;

class UpdateMove : public UpdateEvent {
private:
    Map& map;
    std::string nickname;
    GameType::Direction direction;
    unsigned int distanceTravelled;
    bool reachedDestination;

public:
    UpdateMove(Map& _map, std::string&& _nickname, GameType::Direction _direction,
            unsigned int _distanceTravelled, bool _reachedDestination) : map(_map),
            nickname(std::move(_nickname)), direction(_direction), distanceTravelled(_distanceTravelled),
            reachedDestination(_reachedDestination){}

    void operator()() override;
};


#endif //ARGENTUM_UPDATEMOVE_H
