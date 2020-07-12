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

void Tile::addEntity(std::shared_ptr<Entity>& _entity) {
    entity = _entity;
}

void Tile::renderEntity() {
    if (!entity.expired()) {
        std::shared_ptr<Entity> _entity(entity);
        _entity->render();
    }
    if (!spell.expired()) {
        std::shared_ptr<Spell> _spell(spell);
        _spell->render();
    }
}

void Tile::removeEntity() {
    if (!entity.expired()) {
        std::shared_ptr<Entity> _entity(entity);
        spell = _entity->getSpell();
    }
    entity.reset();
}

void Tile::addSpell(std::shared_ptr<Spell>& newSpell, SDL_Rect& camera) {
    if (!entity.expired()) {
        std::shared_ptr<Entity> _entity(entity);
        _entity->addSpell(newSpell);
    } else {
        spell = newSpell;
    }
}

void Tile::destroyItem() {
    item.setItem(nullptr);
}
