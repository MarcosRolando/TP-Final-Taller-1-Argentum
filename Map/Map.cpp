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
            if (x >= LEVEL_WIDTH) continue;
            if (y >= LEVEL_HEIGHT) continue;
            int xTile = floor(x / TILE_WIDTH);
            int yTile = floor(y / TILE_HEIGHT);
            int tile = yTile*TOTAL_HORIZONTAL_TILES + xTile;
            tiles[tile].renderGround(camera);
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
    for (int i = -1; i < (VISIBLE_VERTICAL_TILES + 1); ++i) {
        for (int j = -1; j < (VISIBLE_HORIZONTAL_TILES + 1); ++j) {
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
                       TextureID entity, std::string&& npcNickname) {
    unsigned int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    if (structure != Nothing) {
        tiles[tile].loadData(textureRepo.getTexture(floor.texture),
                &textureRepo.getTexture(structure), floor.index);
    } else {
        tiles[tile].loadData(textureRepo.getTexture(floor.texture),
                nullptr, floor.index);
    }
    if (entity != Nothing) {
        addNPC(entity, std::move(npcNickname), position);
    }
}

void Map::addNPC(TextureID entity, std::string&& nickname, Coordinate position) {
    int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles[tile].addEntity(std::unique_ptr<Entity>(new NPC(textureRepo,
            camera, position.j*TILE_WIDTH,position.i*TILE_HEIGHT, entity)));
    entities.emplace(nickname, position);
}

void Map::addPlayer(PlayerEquipment equipment, bool isAlive, std::string&& nickname,
                                                            Coordinate position) {
    int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles[tile].addEntity(std::unique_ptr<Entity>(new Player(textureRepo,
            camera, position.j*TILE_WIDTH,position.i*TILE_HEIGHT, equipment, isAlive)));
    entities.emplace(nickname, position);
}

void Map::loadTileItem(Coordinate position, TextureID itemTexture) {
    unsigned int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles[tile].loadItem(textureRepo.getTexture(itemTexture));
}

void Map::moveEntity(std::string &nickname, GameType::Direction direction,
                     unsigned int distanceTravelled, bool reachedDestination) {

    Coordinate entityPosition = entities.at(nickname);
    int tile = entityPosition.i * TOTAL_HORIZONTAL_TILES + entityPosition.j;
    tiles[tile].moveEntity(direction, distanceTravelled, movingEntities);
    if (reachedDestination) {
        std::unique_ptr<Entity> entity = tiles[tile].getEntity();
        entityPosition = _calculateNewTile(entityPosition, direction);
        tile = entityPosition.i * TOTAL_HORIZONTAL_TILES + entityPosition.j;
        tiles[tile].addEntity(std::move(entity));
        auto it = entities.find(nickname);
        it->second = entityPosition;
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

bool _finishedMoving(const Entity* entity) {
    return entity->finishedMoving();
}

void Map::updateInterpolation(float timeStep) {
    for (auto & entity : movingEntities) {
        entity->updatePosition(timeStep);
    }
    movingEntities.erase(std::remove_if(movingEntities.begin(), movingEntities.end(),
                                        _finishedMoving), movingEntities.end());
}
