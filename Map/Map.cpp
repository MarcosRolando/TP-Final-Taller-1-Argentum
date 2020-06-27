//
// Created by marcos on 6/7/20.
//

#include "Map.h"
#include <fstream>
#include "../GameConstants.h"
#include "../MapFileReader.h"

Map::Map(TextureRepository& repo, SDL_Rect& camera) : textureRepo(repo), camera(camera) {
    this->camera = camera;
    //_setTiles();
}
/*
void Map::_setTiles() {
    MapFileReader mapFile("../map.json");

    for (int j = 0; j < TOTAL_HORIZONTAL_TILES; ++j) {
        for (int i = 0; i < TOTAL_VERTICAL_TILES; ++i) {
            TileInfo tileInfo = mapFile.getTileInfo(j, i);
            int x = i*TILE_WIDTH;
            int y = j*TILE_HEIGHT;

            if (tileInfo.tileType.find("DeadGrass") != (size_t )-1) {
                tiles.emplace_back(x, y, (int)tileInfo.tileType[9] - 48, textureRepo.getTexture(DeadGrass));
            } else if (tileInfo.tileType.find("PrettyGrass") != (size_t )-1) {
                tiles.emplace_back(x, y, (int) tileInfo.tileType[11] - 48,textureRepo.getTexture(PrettyGrass));
            } else if (tileInfo.tileType.find("PrettyRoad") != (size_t )-1) {
                tiles.emplace_back(x, y, (int) tileInfo.tileType[10] - 48,textureRepo.getTexture(PrettyRoad));
            } else if (tileInfo.tileType.find("Grass") != (size_t )-1) {
                tiles.emplace_back(x, y, (int)tileInfo.tileType[5] - 48, textureRepo.getTexture(Grass));
            } else if (tileInfo.tileType.find("DarkWater") != (size_t )-1) {
                tiles.emplace_back(x, y, (int) tileInfo.tileType[9] - 48,textureRepo.getTexture(DarkWater));
            } else if (tileInfo.tileType.find("Water") != (size_t )-1) {
                tiles.emplace_back(x, y, (int) tileInfo.tileType[5] - 48,textureRepo.getTexture(Water));
            } else if (tileInfo.tileType == "Sand") {
                tiles.emplace_back(x, y, 0,textureRepo.getTexture(Sand));
            } else {
                tiles.emplace_back(x, y, 0, textureRepo.getTexture(Water));
            }

            if (tileInfo.structureType == "BoneGuy") {
                tiles.back().setStructure(textureRepo.getTexture(BoneGuy));
            } else if (tileInfo.structureType == "BrokenRipStone") {
                tiles.back().setStructure(textureRepo.getTexture(BrokenRipStone));
            } else if (tileInfo.structureType == "Bush") {
                tiles.back().setStructure(textureRepo.getTexture(Bush));
            } else if (tileInfo.structureType == "DeadBush") {
                tiles.back().setStructure(textureRepo.getTexture(DeadBush));
            } else if (tileInfo.structureType == "DeadGuy") {
                tiles.back().setStructure(textureRepo.getTexture(DeadGuy));
            } else if (tileInfo.structureType == "DeadTree") {
                tiles.back().setStructure(textureRepo.getTexture(DeadTree));
            } else if (tileInfo.structureType == "FatTree") {
                tiles.back().setStructure(textureRepo.getTexture(FatTree));
            } else if (tileInfo.structureType == "HangedGuy") {
                tiles.back().setStructure(textureRepo.getTexture(HangedGuy));
            } else if (tileInfo.structureType == "House1") {
                tiles.back().setStructure(textureRepo.getTexture(House1));
            } else if (tileInfo.structureType == "House2") {
                tiles.back().setStructure(textureRepo.getTexture(House2));
            } else if (tileInfo.structureType == "House3") {
                tiles.back().setStructure(textureRepo.getTexture(House3));
            } else if (tileInfo.structureType == "LongTree") {
                tiles.back().setStructure(textureRepo.getTexture(LongTree));
            } else if (tileInfo.structureType == "PalmTree") {
                tiles.back().setStructure(textureRepo.getTexture(PalmTree));
            } else if (tileInfo.structureType == "RipStone") {
                tiles.back().setStructure(textureRepo.getTexture(RipStone));
            } else if (tileInfo.structureType == "Tree") {
                tiles.back().setStructure(textureRepo.getTexture(Tree));
            } else if (tileInfo.structureType == "VeryDeadGuy") {
                tiles.back().setStructure(textureRepo.getTexture(VeryDeadGuy));
            } else if (tileInfo.structureType == "SunkenColumn") {
                tiles.back().setStructure(textureRepo.getTexture(SunkenColumn));
            } else if (tileInfo.structureType == "SunkenShip") {
                tiles.back().setStructure(textureRepo.getTexture(SunkenShip));
            }

            if (tileInfo.entityType == "Banker") {
                npcs.emplace_back(textureRepo, camera, x, y, Banker);
            } else if (tileInfo.entityType == "Priest") {
                npcs.emplace_back(textureRepo, camera, x, y, Priest);
            } else if (tileInfo.entityType == "Trader") {
                npcs.emplace_back(textureRepo, camera, x, y, Trader);
            }
        }
    }
}
*/
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
    for (auto & npc : npcs) {
        npc.render(timeStep);
    }
}

void Map::setSize(int rows, int columns) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            tiles.emplace_back(j*TILE_WIDTH, i*TILE_HEIGHT);
        }
    }
}

void Map::loadTileData(unsigned int i, unsigned int j, FloorTypeTexture floor, TextureID structure,
                       TextureID entity) {
    unsigned int tile = i*TOTAL_HORIZONTAL_TILES + j;
    if (structure != Nothing) {
        tiles[tile].loadData(textureRepo.getTexture(floor.texture),
                &textureRepo.getTexture(structure), floor.index);
    } else {
        tiles[tile].loadData(textureRepo.getTexture(floor.texture),
                nullptr, floor.index);
    }
    if (entity != Nothing) {
        addEntity(entity, i, j);
    }
}

void Map::addEntity(TextureID entity, unsigned int i, unsigned int j) {
    npcs.emplace_back(textureRepo, camera, j*TILE_WIDTH, i*TILE_HEIGHT, entity);
}
