//
// Created by marcos on 7/2/20.
//

#ifndef ARGENTUM_UPDATEGUI_H
#define ARGENTUM_UPDATEGUI_H

#include "UpdateEvent.h"
#include "../Client/EntityData.h"

class UpdateGUI : public UpdateEvent {
private:
    PlayerData data;

public:
    explicit UpdateGUI(PlayerData&& _data) : data(std::move(_data)) {}
    void operator()(GameGUI& game) override;
};


#endif //ARGENTUM_UPDATEGUI_H
