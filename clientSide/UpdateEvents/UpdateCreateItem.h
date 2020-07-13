//
// Created by marcos on 7/5/20.
//

#ifndef ARGENTUM_UPDATECREATEITEM_H
#define ARGENTUM_UPDATECREATEITEM_H

#include "UpdateEvent.h"
#include "../../libs/GameEnums.h"
#include "../Map/Coordinate.h"
#include "../Texture/TextureID.h"

class UpdateCreateItem : public UpdateEvent {
private:
    TextureID item;
    Coordinate position{};

public:
    UpdateCreateItem(GameType::ItemType _type, int32_t _item, Coordinate _position);
    void operator()(GameGUI& game) override;
};


#endif //ARGENTUM_UPDATECREATEITEM_H
