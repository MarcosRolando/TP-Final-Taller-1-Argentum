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
    ItemData itemData = game.storeItemFromTileInPlayer(player);
    std::stringstream data;
    if (itemData.id != -1) {
        msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::DESTROY_ITEM);
        msgpack::pack(data, messageTypeData);
        msgpack::type::tuple<int32_t, int32_t> itemDataTuple
                        (itemData.coordinate.iPosition, itemData.coordinate.jPosition);
        msgpack::pack(data, itemDataTuple);
        protocol.addToGeneralData(data);
    } else if (itemData.id >= 0) {
        msgpack::type::tuple<GameType::EventID> messageTypeData(GameType::CREATE_ITEM);
        msgpack::pack(data, messageTypeData);
        msgpack::type::tuple<GameType::ItemType, int32_t, int32_t, int32_t> itemDataTuple
                (itemData.type, itemData.id, itemData.coordinate.iPosition, itemData.coordinate.jPosition);
        msgpack::pack(data, itemDataTuple);
        protocol.addToGeneralData(data);
    }
}
