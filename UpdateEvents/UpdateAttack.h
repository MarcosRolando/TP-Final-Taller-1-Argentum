//
// Created by marcos on 7/7/20.
//

#ifndef ARGENTUM_UPDATEATTACK_H
#define ARGENTUM_UPDATEATTACK_H

#include "UpdateEvent.h"
#include "../Map/Coordinate.h"
#include "../Shared/GameEnums.h"

class UpdateAttack : public UpdateEvent {
private:
    Coordinate position;
    GameType::Weapon weapon;

public:
    UpdateAttack(Coordinate _position, GameType::Weapon _weapon) : position(_position),
                weapon(_weapon) {}

    void operator()(GameGUI& game) override;
};


#endif //ARGENTUM_UPDATEATTACK_H
