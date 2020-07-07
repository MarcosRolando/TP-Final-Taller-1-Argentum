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

void Tile::createItem(Texture& _itemTexture) {
    item.setItem(_itemTexture);
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
    if (spell) {
        spell->render();
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

std::unique_ptr<Spell>* Tile::removeEntity() {
    if (entity) {
        spell = entity->getSpell();
        entity = nullptr;
        return &spell;
    }
    entity = nullptr;
    return nullptr;
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

std::unique_ptr<Spell>* Tile::addSpell(Texture& spellTexture, SDL_Rect& camera, float x, float y) {
    spell.reset(new Spell(spellTexture, camera, x, y));
    if (entity) {
        return entity->addSpell(std::move(spell));
    } else {
        return &spell;
    }
}
