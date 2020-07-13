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
    Coordinate position{};
    GameType::Weapon weapon;
    GameType::Direction attackDir;

public:
    UpdateAttack(Coordinate _position, int32_t _weapon, GameType::Direction _attackDir);
    void operator()(GameGUI& game) override;
};


#endif //ARGENTUM_UPDATEATTACK_H
