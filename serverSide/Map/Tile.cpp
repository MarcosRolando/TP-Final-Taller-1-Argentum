//
// Created by agustin on 6/6/20.
//

#include "Tile.h"
#include <memory>
#include "../Entities/AttackResult.h"
#include "../../libs/TPException.h"
#include "../Items/Item.h"
#include "../Entities/Player.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::FloorType)
MSGPACK_ADD_ENUM(GameType::Entity)
MSGPACK_ADD_ENUM(GameType::Structure)

#define NO_ITEMS_MESSAGE "There are no entities or items on this tille\n"
#define ITEMS_MESSAGE "The stored items are:\n"

////////////////////////////////////////PUBLIC////////////////////////////////////////

Tile::Tile(bool _isOccupable, bool _isFromCity, GameType::FloorType _floor, GameType::Structure _structure,
           std::shared_ptr<Entity>&& initialEntity): entity(nullptr) {
    floor = _floor;
    structure = _structure;
    isFromCity = _isFromCity;
    isOccupable = _isOccupable;

    if (isOccupable && initialEntity) {
        entity = std::move(initialEntity);
        isOccupable = false;
    }
}

void Tile::moveEntity(Tile& otherTile, Coordinate position) {
    this->entity = std::move(otherTile.entity);
    otherTile.entity = nullptr;
    entity->move(position);
    isOccupable = false;
    otherTile.isOccupable = true;
}

void Tile::addEntity(std::shared_ptr<Entity>&& received_entity) {
    if (isOccupable) {
        entity = std::move(received_entity);
        isOccupable = false;
    } else {
        throw TPException("Tried to add an entity to a non occupable tile!");
    }
}

void Tile::removeEntity() {
    if (entity) {
        entity.reset();
        isOccupable = true;
    }
}

void Tile::addItem(std::shared_ptr<Item>&& received_item) {
    if (received_item) {
        items.push_back(std::move(received_item));
    }
}

std::shared_ptr<Item> Tile::removeItem() {
    if (items.empty()) {
        return nullptr;
    }
    std::shared_ptr<Item> return_item = items.back();
    items.pop_back();
    return return_item;
}

std::pair<AttackResult, bool> Tile::attacked(int damage, unsigned int level, bool isAPlayer) {
    if (isFromCity) {
        return {{0, 0, "You can't attack a tile inside a city\n"}, false};
    }
    if (!entity) {
        return {{0, 0, ""}, true};
    }
    return {entity->attacked(damage, level, isAPlayer), true};
}

bool Tile::hasMonsterTarget() const {
    if (entity) {
        return entity->isMonsterTarget();
    }
    return false;
}

bool Tile::isAvailable() const {
    return isOccupable;
}

void Tile::list(Player &player) {
    if (entity) {
        entity->list(player);
    } else {
        _storeItemsNames(player);
    }
}


void Tile::withdraw(Player &player, const std::string &itemName) {
    if (entity) {
        entity->withdraw(player, itemName);
    }
}

void Tile::deposit(Player &player, const std::string &itemName) {
    if (entity) {
        entity->deposit(player, itemName);
    }
}

void Tile::buy(Player &player, const std::string &itemName) {
    if (entity) {
        entity->buy(player, itemName);
    }
}

void Tile::sell(Player &player, const std::string &itemName) {
    if (entity) {
        entity->sell(player, itemName);
    }
}

void Tile::addItem(std::list<std::shared_ptr<Item>>&& _items) {
    for (auto & item : _items) {
        if (item) {
            items.push_back(std::move(item));
        }
    }
}

bool Tile::isInCity() const {
    return isFromCity;
}

void Tile::operator>>(std::stringstream &mapBuffer) const {
    GameType::Entity entityType = GameType::Entity::NOTHING;
    std::string nickname = "";
    if (entity) {
        entityType = entity->getType();
        nickname = entity->getNickname();
    }
    /*de izquierda a derecha es el tipo de piso, tipo de estructura y citizen*/
    msgpack::type::tuple<GameType::FloorType, GameType::Structure,
            GameType::Entity, std::string> tileInfo(floor, structure, entityType, nickname);
    msgpack::pack(mapBuffer, tileInfo);
}

const Item* Tile::peekShowedItemData() {
    if (items.empty()) {
        return nullptr;
    }
    return items.back().get();
}

void Tile::requestRestore(Player& player) {
    if (entity) {
        entity->requestHeal(player);
    }
}

//////////////////////////PRIVATE///////////////////////////////////

void Tile::_storeItemsNames(Player& player) {
    if (!items.empty()) {
        player.addMessage(ITEMS_MESSAGE);
        for (const auto & item: items) {
            player.addMessage(item->getName() + "\n");
        }
    }
}

