//
// Created by marcos on 6/7/20.
//

#include "Map.h"
#include <fstream>
#include "../GameConstants.h"
#include "../MapFileReader.h"
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

void Map::renderNPCS(float timeStep) {
    for (int i = -1; i < (VISIBLE_VERTICAL_TILES + 3); ++i) {
        for (int j = -1; j < (VISIBLE_HORIZONTAL_TILES + 3); ++j) {
            float x = (float)camera.x + (float)j * TILE_WIDTH;
            float y = (float)camera.y + (float)i * TILE_HEIGHT;
            if (x >= LEVEL_WIDTH || x < 0) continue;
            if (y >= LEVEL_HEIGHT || y < 0) continue;
            int xTile = floor(x / TILE_WIDTH);
            int yTile = floor(y / TILE_HEIGHT);
            int tile = yTile*TOTAL_HORIZONTAL_TILES + xTile;
            tiles.at(tile).renderEntity(timeStep);
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
                     unsigned int distanceTraveled, bool reachedDestination) {

    Coordinate entityPosition = entities.at(nickname);
    int tile = entityPosition.i * TOTAL_HORIZONTAL_TILES + entityPosition.j;
    tiles[tile].moveEntity(direction, distanceTraveled);
}
