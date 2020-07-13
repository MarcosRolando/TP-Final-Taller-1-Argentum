//
// Created by marcos on 7/9/20.
//

#ifndef ARGENTUM_UPDATETELEPORTENTITY_H
#define ARGENTUM_UPDATETELEPORTENTITY_H

#include "UpdateEvent.h"
#include <string>
#include "../Map/Coordinate.h"

class UpdateTeleportEntity : public UpdateEvent {
private:
    std::string nickname;
    Coordinate newPosition;

public:
    UpdateTeleportEntity(std::string&& _nickname, Coordinate _position) :
                        nickname(_nickname), newPosition(_position) {}

    void operator()(GameGUI& game) override;
};


#endif //ARGENTUM_UPDATETELEPORTENTITY_H
