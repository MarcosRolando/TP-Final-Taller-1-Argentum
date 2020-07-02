//
// Created by agustin on 6/6/20.
//

#include "Tile.h"
#include <memory>
#include "../AttackResult.h"
#include "../TPException.h"
#include "../Items/Item.h"
#include <msgpack.hpp>

MSGPACK_ADD_ENUM(GameType::FloorType)
MSGPACK_ADD_ENUM(GameType::Entity)
MSGPACK_ADD_ENUM(GameType::Structure)
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

    //FALTA AGREGAR ENTITY
}

void Tile::moveEntity(Tile&& otherTile, Coordinate position) {
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
        throw TPException("Intentaron agregar un entity a un tile no ocupable!");
    }
}

void Tile::removeEntity() {
    entity.reset();
    isOccupable = true;
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
    std::shared_ptr<Item> return_item = items.front();
    items.pop_front();
    return return_item;
}

AttackResult Tile::attacked(int damage, unsigned int level, bool isAPlayer) {
    if (!entity) {
        return {0, 0};
    }
    return entity->attacked(damage, level, isAPlayer);
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

/*
void Tile::list(Player& player, std::list<ProductData> &products) {
    if (entity) {
        entity->list(player, products);
    }
}
*/

void Tile::list(Player &player, std::stringstream &data) {
    if (entity) {
        entity->list(player, data);
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
    if (entity) {
        entityType = entity->getType();
    }
    msgpack::type::tuple<GameType::FloorType,
                GameType::Structure, GameType::Entity> tileInfo(floor, structure, entityType); /*de izquierda a derecha es el tipo de piso, tipo de estructura y citizen*/
    msgpack::pack(mapBuffer, tileInfo);
}

void Tile::storeTileData(std::stringstream &data, uint32_t i, uint32_t j) const {
    if ((entity) && (!entity->isCitizen())) {
        *entity >> data;
    }
    if (!items.empty()) {
        items.front()->loadDropItemData(data, i, j);
    }
}

