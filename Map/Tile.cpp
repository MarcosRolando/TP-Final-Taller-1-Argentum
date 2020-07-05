//
// Created by marcos on 6/7/20.
//

#include "Tile.h"
#include "../GameConstants.h"
#include "../Character/Player.h"

Tile::Tile(Coordinate position) : item(position), structure(position) {
    box = {position.j*TILE_WIDTH, position.i*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
    type = 0;
}

void Tile::renderGround(SDL_Rect& camera) {
    //If the tile is on screen
    tileTexture->render(box.x - camera.x, box.y - camera.y, type);
    item.render(camera);
}

void Tile::addItemDrop(Texture& itemTexture) {
    item.setItem(itemTexture);
}

void Tile::setStructure(Texture& sTexture) {
    structure.setTexture(sTexture);
}

void Tile::renderStructure(SDL_Rect &camera) {
    structure.render(camera);
}

void Tile::loadData(Texture& _tileTexture, Texture* sTexture, int tileType) {
    type = tileType;
    tileTexture = &_tileTexture;
    if (sTexture) {
        structure.setTexture(*sTexture);
    }
}

void Tile::loadItem(Texture& _itemTexture) {
    item.setItem(_itemTexture);
}

void Tile::addEntity(std::unique_ptr<Entity> _entity) {
    entity = std::move(_entity);
}

void Tile::renderEntity() {
    if (entity) {
        entity->render();
    }
}

void Tile::moveEntity(GameType::Direction direction, unsigned int distanceTravelled,
                      std::list<Entity *> &movingEntities) {
    if (entity) {
        entity->move(direction, distanceTravelled, movingEntities);
    }
}

std::unique_ptr<Entity> Tile::getEntity() {
    std::unique_ptr<Entity> aux = nullptr;
    if (entity) {
        aux = std::move(entity);
        entity.reset();
    }
    return aux;
}

void Tile::setCameraOn() {
    if (entity) {
        entity->activateCamera();
    }
}

void Tile::removeEntity() {
    entity = nullptr;
}

void Tile::equipOnPlayer(GameType::EquipmentPlace place, TextureID equipment) {
    Entity* entityToCast = entity.get();
    auto player = dynamic_cast<Player*>(entityToCast);
    if (player) {
        player->equip(place, equipment);
    }
}
