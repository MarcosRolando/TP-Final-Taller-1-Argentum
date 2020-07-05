//
// Created by marcos on 7/5/20.
//

#ifndef ARGENTUM_UPDATEEQUIP_H
#define ARGENTUM_UPDATEEQUIP_H

#include "UpdateEvent.h"
#include <string>
#include "../Shared/GameEnums.h"
#include "../Texture/TextureID.h"

class UpdateEquip : public UpdateEvent {
private:
    std::string nickname;
    GameType::EquipmentPlace place;
    TextureID equipment;

public:
    UpdateEquip(std::string&& _nickname, GameType::EquipmentPlace _place,
                int32_t _equipment);

    void operator()(GameGUI& game);
};


#endif //ARGENTUM_UPDATEEQUIP_H
