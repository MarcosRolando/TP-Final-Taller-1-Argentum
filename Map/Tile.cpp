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

void Tile::createItem(Texture& _itemTexture) {
    item.setItem(&_itemTexture);
}

void Tile::addEntity(std::unique_ptr<Entity> _entity) {
    if (entity) {
        std::cerr << "pisaste un entity capo" << std::endl;
    }
    entity = std::move(_entity);
}

void Tile::renderEntity() {
    if (entity) {
        entity->render();
    }
    if (!spell.expired()) {
        std::shared_ptr<Spell> _spell(spell);
        _spell->render();
    }
}

GameType::Direction Tile::moveEntity(GameType::Direction direction, unsigned int distanceTravelled,
                        bool reachedDestination) {
    if (entity) {
        return entity->move(direction, distanceTravelled, reachedDestination);
    }
    throw TPException("Intentaron mover una entity que no existia en el tile");
}

std::unique_ptr<Entity> Tile::getEntity() {
    if (entity) {
        return std::move(entity);
    }
    return nullptr;
}

void Tile::setCameraOn() {
    if (entity) {
        entity->activateCamera();
    }
}

void Tile::removeEntity() {
    if (entity) {
        spell = entity->getSpell(); /*Para que la animacion quede y no muera si mataste al entity*/
        entity = nullptr;
    }
}

void Tile::equipOnPlayer(GameType::EquipmentPlace place, TextureID equipment) {
    Entity* entityToCast = entity.get();
    auto player = dynamic_cast<Player*>(entityToCast);
    if (player) {
        player->equip(place, equipment);
    }
}

void Tile::killPlayer() {
    Entity* entityToCast = entity.get();
    auto player = dynamic_cast<Player*>(entityToCast);
    if (player) {
        player->kill();
    }
}

void Tile::revivePlayer() {
    Entity* entityToCast = entity.get();
    auto player = dynamic_cast<Player*>(entityToCast);
    if (player) {
        player->revive();
    }
}

void Tile::addSpell(std::shared_ptr<Spell>& newSpell, SDL_Rect& camera, float x, float y) {
    if (entity) {
        entity->addSpell(newSpell);
    } else {
        spell = newSpell;
    }
}

void Tile::destroyItem() {
    item.setItem(nullptr);
}
