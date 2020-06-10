//
// Created by agustin on 6/6/20.
//

#include "Tile.h"

#include <memory>
#include "FloorType.h"

Tile::Tile(FloorType floor): entity(nullptr){
    this->floor = floor;
    switch (floor) {
        case FLOOR_TYPE_TREE:
        case FLOOR_TYPE_WALL:
            isOccupable = false;
            break;
        default:
            isOccupable = true;
    }
}


Tile::Tile(Tile &&other) noexcept {
    std::unique_ptr<Entity> aux = std::move(other.entity);
    other.entity = std::move(this->entity);
    this->entity = std::move(aux);
}

bool Tile::addEntity(Entity *received_entity) {
    if (isOccupable) {
        this->entity.reset(received_entity);
        isOccupable = false;
        return true;
    }
    return false;
}

void Tile::removeEntity() {
    entity.reset(nullptr);
    isOccupable = true;
}

void Tile::addItem(Item *received_item) {
    items.emplace_back(received_item);
}

std::shared_ptr<Item> Tile::removeItem() {
    if (items.empty()) {
        return nullptr;
    }
    std::shared_ptr<Item> return_item = items.front();
    items.pop_front();
    return return_item;
}

unsigned int Tile::attacked(unsigned int damage, unsigned int level) {
    if (!entity) {
        return 0;
    }
    return entity->attacked(damage, level);
}

bool Tile::hasMonsterTarget() {
    if (entity) {
        return entity->isMonsterTarget();
    }
    return false;
}


