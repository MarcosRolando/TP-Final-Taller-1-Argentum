//
// Created by marcos on 7/2/20.
//

#ifndef ARGENTUM_UPDATECREATENPC_H
#define ARGENTUM_UPDATECREATENPC_H

#include "UpdateEvent.h"
#include "../Client/ClientProtocol.h"

class UpdateCreateNPC : public UpdateEvent {
private:
    EntityData data;
public:
    explicit UpdateCreateNPC(EntityData& _data) : data(_data) {}
    void operator()(GameGUI& game);
};

#endif //ARGENTUM_UPDATECREATENPC_H
