//
// Created by agustin on 6/6/20.
//

#include "Tile.h"
#include <memory>
#include "FloorType.h"
#include "../AttackResult.h"
#include "../TPException.h"
#include <msgpack.hpp>

////////////////////////////////////////PUBLIC////////////////////////////////////////



Tile::Tile(bool isFromCity, FloorType floor): entity(nullptr) {
    this->floor = floor;
    this->isFromCity = isFromCity;
    switch (floor) {
        case FLOOR_TYPE_TREE:
        case FLOOR_TYPE_WALL:
            isOccupable = false;
            break;
        default:
            isOccupable = true;
    }
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

unsigned int Tile::list(Player& player, std::list<ProductData> &products) {
    if (!entity) {
        return 0;
    }
    return entity->list(player, products);
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

void Tile::operator>>(std::stringstream &mapBuffer) {
    msgpack::type::tuple<>
}
