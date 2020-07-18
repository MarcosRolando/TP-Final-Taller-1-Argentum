//
// Created by marcos on 6/7/20.
//

#include "Tile.h"
#include "../Client/GameConstants.h"
#include "../Character/Player.h"

Tile::Tile(Coordinate position) : item(position), structure(position) {
    box = {position.j*TILE_WIDTH, position.i*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
    type = 0;
}

void Tile::renderGround(SDL_Rect& camera) {
    //Si se ve el tile en la pantalla
    tileTexture->render(box.x - camera.x, box.y - camera.y, type);
    item.render(camera);
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

void Tile::addEntity(std::shared_ptr<Entity>& _entity) {
    entity = _entity;
}

void Tile::renderEntity() {
    auto _entity = entity.lock();
    if (_entity) {
        _entity->render();
    }
    auto _spell = spell.lock();
    if (_spell) {
        _spell->render();
    }
}

void Tile::removeEntity() {
    auto _entity = entity.lock();
    if (_entity) {
        spell = _entity->getSpell();
    }
    entity.reset();
}

void Tile::addSpell(std::shared_ptr<Spell>& newSpell, SDL_Rect& camera) {
    auto _entity = entity.lock();
    if (_entity) {
        _entity->addSpell(newSpell);
    } else {
        spell = newSpell;
    }
}

void Tile::destroyItem() {
    item.setItem(nullptr);
}
