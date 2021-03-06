//
// Created by agustin on 23/6/20.
//

#include "Drop.h"
#include "../../Entities/Player.h"
#include "../../Items/ItemData.h"
#include "../../Server/ServerProtocol.h"
#include "../Game.h"
#include "../../Items/Item.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::ItemType)


Drop::Drop(Player &_player, int _inventoryPosition) {
    player = &_player;
    inventoryPosition = _inventoryPosition;
    dropPosition = player->getPosition();
}

Drop::Drop(Game& _game, std::list<std::shared_ptr<Item>>&& _items, Coordinate _dropPosition) {
    game = &_game;
    dropPosition = _dropPosition;
    if (_items.empty()) {
        throw std::invalid_argument("List without elements in Drop");
    }
    items = std::move(_items);
}

Drop::Drop(Game &_game, std::shared_ptr<Item> &&item, Coordinate _dropPosition) {
    game = &_game;
    dropPosition = _dropPosition;
    items.push_back(std::move(item));
}

void Drop::operator()(ServerProtocol& protocol) {
    const Item* itemPtr = nullptr;
    if (player) {
        itemPtr = player->dropItem(inventoryPosition);
    } else {
        itemPtr = items.back().get();
        game->dropItems(std::move(items), dropPosition);
    }
    if (itemPtr) {
        std::stringstream data;
        itemPtr->loadDropItemData(data, dropPosition.iPosition, dropPosition.jPosition);
        protocol.addToGeneralData(data);
    }
}
