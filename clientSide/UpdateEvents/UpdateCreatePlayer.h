//
// Created by ivan on 1/7/20.
//

#ifndef ARGENTUM_UPDATECREATEPLAYER_H
#define ARGENTUM_UPDATECREATEPLAYER_H

#include "UpdateEvent.h"
#include <string>
#include "../../libs/GameEnums.h"
#include "../Client/ClientProtocol.h"

class UpdateCreatePlayer : public UpdateEvent{
private:
    MapPlayerData data;

public:
    explicit UpdateCreatePlayer(MapPlayerData& _data) : data(_data) {}
    void operator()(GameGUI& game) override;
};


#endif //ARGENTUM_UPDATECREATEPLAYER_H
