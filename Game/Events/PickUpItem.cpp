//
// Created by agustin on 6/7/20.
//

#include "PickUpItem.h"
#include "../../Entities/Player.h"
#include "../Game.h"
#include "../../Server/ServerProtocol.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::ItemType)

PickUpItem::PickUpItem(Game &game, Player &player): game(game), player(player) {

}

void PickUpItem::operator()(ServerProtocol& protocol) {
    const Item* itemPtr = game.storeItemFromTileInPlayer(player);
    std::stringstream data;
    Coordinate pickUpPosition = player.getPosition();
    if (itemPtr) {
        itemPtr->loadDropItemData(data, pickUpPosition.iPosition, pickUpPosition.jPosition);
        protocol.addToGeneralData(data);
    } else {
        msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::DESTROY_ITEM);
        msgpack::pack(data, messageTypeData);
        msgpack::type::tuple<int32_t, int32_t> itemDataTuple
                (pickUpPosition.iPosition, pickUpPosition.jPosition);
        msgpack::pack(data, itemDataTuple);
        protocol.addToGeneralData(data);
    }
}
