//
// Created by marcos on 6/29/20.
//

#ifndef ARGENTUM_UPDATEMOVE_H
#define ARGENTUM_UPDATEMOVE_H

#include "UpdateEvent.h"
#include <string>
#include "../Shared/GameEnums.h"

class UpdateMove : public UpdateEvent {
private:
    std::string nickname;
    GameType::Direction direction;
    unsigned int distanceTravelled;
    bool reachedDestination;

public:
    UpdateMove(std::string&& _nickname, GameType::Direction _direction,
            unsigned int _distanceTravelled, bool _reachedDestination) :
            nickname(std::move(_nickname)), direction(_direction), distanceTravelled(_distanceTravelled),
            reachedDestination(_reachedDestination){}

    void operator()(GameGUI& game) override;
};


#endif //ARGENTUM_UPDATEMOVE_H
