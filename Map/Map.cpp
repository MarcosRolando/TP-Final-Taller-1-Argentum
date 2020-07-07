//
// Created by marcos on 6/7/20.
//

#include "Map.h"
#include <fstream>
#include <algorithm>
#include "../GameConstants.h"
#include "../Character/NPC.h"
#include "../Character/Player.h"

Map::Map(TextureRepository& repo, SDL_Rect& camera) : textureRepo(repo), camera(camera) {
    this->camera = camera;
}

void Map::renderGround() {
    for (int i = 0; i < (VISIBLE_VERTICAL_TILES + 1); ++i) {
        for (int j = 0; j < (VISIBLE_HORIZONTAL_TILES + 1); ++j) {
            float x = (float)camera.x + (float)j * TILE_WIDTH;
            float y = (float)camera.y + (float)i * TILE_HEIGHT;
            if (x >= LEVEL_WIDTH || x < 0) continue;
            if (y >= LEVEL_HEIGHT || y < 0) continue;
            int xTile = floor(x / TILE_WIDTH);
            int yTile = floor(y / TILE_HEIGHT);
            int tile = yTile*TOTAL_HORIZONTAL_TILES + xTile;
            tiles.at(tile).renderGround(camera);
        }
    }
}

void Map::renderStructures() {
    for (int i = -1; i < (VISIBLE_VERTICAL_TILES + 3); ++i) {
        for (int j = -1; j < (VISIBLE_HORIZONTAL_TILES + 3); ++j) {
            float x = (float)camera.x + (float)j * TILE_WIDTH;
            float y = (float)camera.y + (float)i * TILE_HEIGHT;
            if (x >= LEVEL_WIDTH || x < 0) continue;
            if (y >= LEVEL_HEIGHT || y < 0) continue;
            int xTile = floor(x / TILE_WIDTH);
            int yTile = floor(y / TILE_HEIGHT);
            int tile = yTile*TOTAL_HORIZONTAL_TILES + xTile;
            tiles.at(tile).renderStructure(camera);
        }
    }
}

void Map::renderNPCS() {
    for (int i = -2; i < (VISIBLE_VERTICAL_TILES + 2); ++i) {
        for (int j = -2; j < (VISIBLE_HORIZONTAL_TILES + 2); ++j) {
            float x = (float)camera.x + (float)j * TILE_WIDTH;
            float y = (float)camera.y + (float)i * TILE_HEIGHT;
            if (x >= LEVEL_WIDTH || x < 0) continue;
            if (y >= LEVEL_HEIGHT || y < 0) continue;
            int xTile = floor(x / TILE_WIDTH);
            int yTile = floor(y / TILE_HEIGHT);
            int tile = yTile*TOTAL_HORIZONTAL_TILES + xTile;
            tiles.at(tile).renderEntity();
        }
    }
}

void Map::setSize(int rows, int columns) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            tiles.emplace_back(Coordinate{i, j});
        }
    }
}

void Map::loadTileData(Coordinate position, FloorTypeTexture floor, TextureID structure,
                       TextureID entity) {
    unsigned int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    if (structure != Nothing) {
        tiles.at(tile).loadData(textureRepo.getTexture(floor.texture),
                &textureRepo.getTexture(structure), floor.index);
    } else {
        tiles.at(tile).loadData(textureRepo.getTexture(floor.texture),
                nullptr, floor.index);
    }
    if (entity != Nothing) {
        EntityData data = {entity, "", position,
                           GameType::DIRECTION_STILL, 0};
        addNPC(data);
    }
}

void Map::addNPC(EntityData& data) {
    if (entities.count(data.nickname) == 0) {
        int tile = data.pos.i*TOTAL_HORIZONTAL_TILES + data.pos.j;
        tiles.at(tile).addEntity(std::unique_ptr<Entity>(new NPC(textureRepo,
                camera, data.pos.j*TILE_WIDTH,data.pos.i*TILE_HEIGHT, data.texture)));
        if (data.currentDir != GameType::DIRECTION_STILL) {
            tiles.at(tile).moveEntity(data.currentDir, data.distanceMoved, false);
        }
        entities.emplace(std::move(data.nickname), data.pos); //todo recibir el nickname de los citizens sino no los cargo
    }
}

void Map::addPlayer(MapPlayerData& playerData) {
    if (entities.count(playerData.entityData.nickname) == 0) {
        int tile = playerData.entityData.pos.i*TOTAL_HORIZONTAL_TILES + playerData.entityData.pos.j;
        tiles.at(tile).addEntity(std::unique_ptr<Entity>(new Player(textureRepo,
                camera, playerData.entityData.pos.j*TILE_WIDTH,playerData.entityData.pos.i*TILE_HEIGHT,
                playerData.equipment, playerData.isAlive)));
        if (playerData.entityData.currentDir != GameType::DIRECTION_STILL) {
            tiles.at(tile).moveEntity(playerData.entityData.currentDir,
                    playerData.entityData.distanceMoved, false);
        }
        entities.emplace(std::move(playerData.entityData.nickname), playerData.entityData.pos);
    }
}

void Map::createItem(Coordinate position, TextureID itemTexture) {
    unsigned int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).createItem(textureRepo.getTexture(itemTexture));
}

void Map::moveEntity(std::string &nickname, GameType::Direction direction,
                     unsigned int distanceTravelled, bool reachedDestination) {

    if (entities.count(nickname) == 1) {
        Coordinate entityPosition = entities.at(nickname);
        int tile = entityPosition.i * TOTAL_HORIZONTAL_TILES + entityPosition.j;
        tiles.at(tile).moveEntity(direction, distanceTravelled, reachedDestination);
        if (reachedDestination) {
            std::unique_ptr<Entity> entity = tiles.at(tile).getEntity();
            entityPosition = _calculateNewTile(entityPosition, direction);
            entitiesToUpdateTilePosition.emplace_back(std::move(entity), entityPosition,
                                                std::move(nickname));
        }
    }
}

Coordinate Map::_calculateNewTile(Coordinate position, GameType::Direction direction) {
    switch (direction) {
        case GameType::DIRECTION_UP:
            position.i -= 1;
            break;
        case GameType::DIRECTION_DOWN:
            position.i += 1;
            break;
        case GameType::DIRECTION_LEFT:
            position.j -= 1;
            break;
        case GameType::DIRECTION_RIGHT:
            position.j += 1;
            break;
        case GameType::DIRECTION_STILL:
            //do nothing
            break;
    }
    return position;
}

void Map::moveEntitiesToNewTile() {
    if (!entitiesToUpdateTilePosition.empty()) {
        for (auto && entity : entitiesToUpdateTilePosition) {
            int tile = std::get<1>(entity).i * TOTAL_HORIZONTAL_TILES + std::get<1>(entity).j;
            tiles.at(tile).addEntity(std::move(std::get<0>(entity)));
            entities.at(std::get<2>(entity)) = std::get<1>(entity);
        }
        entitiesToUpdateTilePosition.clear();
    }

}

void Map::setCameraOn(Coordinate position) {
    int tile = position.i * TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).setCameraOn();
}

void Map::removeEntity(std::string &nickname) {
    Coordinate position = entities.at(nickname);
    int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).removeEntity();
    entities.erase(nickname);
}

void Map::equipOnPlayer(std::string &nickname, GameType::EquipmentPlace place,
                        TextureID equipment) {
    Coordinate position = entities.at(nickname);
    int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).equipOnPlayer(place, equipment);
}

void Map::killPlayer(std::string &nickname) {
    Coordinate position = entities.at(nickname);
    int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).killPlayer();
}
