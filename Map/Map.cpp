//
// Created by marcos on 6/7/20.
//

#include "Map.h"
#include <fstream>
#include "../GameConstants.h"
#include "../MapFileReader.h"

Map::Map(TextureRepository& repo, SDL_Rect& camera) : textureRepo(repo), camera(camera) {
    this->camera = camera;
    _setTiles();
}

void Map::_setTiles() {
    MapFileReader mapFile("../map.json");

    for (int j = 0; j < TOTAL_HORIZONTAL_TILES; ++j) {
        for (int i = 0; i < TOTAL_VERTICAL_TILES; ++i) {
            std::string tileType = mapFile.getTile(j, i);
            std::string structureType = mapFile.getStructure(j, i);
            int x = i*TILE_WIDTH;
            int y = j*TILE_HEIGHT;
            if (tileType.find("DeadGrass") != (size_t )-1) {
                tiles.emplace_back(x, y, (int)tileType[9] - 48, textureRepo.getTexture(DeadGrass));
            } else if (tileType.find("Grass") != (size_t )-1) {
                tiles.emplace_back(x, y, (int)tileType[5] - 48, textureRepo.getTexture(Grass));
            } else if (tileType.find("DarkWater") != (size_t )-1) {
                tiles.emplace_back(x, y, (int) tileType[9] - 48,textureRepo.getTexture(DarkWater));
            } else if (tileType.find("Water") != (size_t )-1) {
                tiles.emplace_back(x, y, (int) tileType[5] - 48,textureRepo.getTexture(Water));
            } else if (tileType == "Sand") {
                tiles.emplace_back(x, y, 0,textureRepo.getTexture(Sand));
            } else {
                tiles.emplace_back(x, y, 0, textureRepo.getTexture(Water));
            }
            if (structureType == "BoneGuy") {
                tiles.back().setStructure(textureRepo.getTexture(BoneGuy));
            } else if (structureType == "BrokenRipStone") {
                tiles.back().setStructure(textureRepo.getTexture(BrokenRipStone));
            } else if (structureType == "Bush") {
                tiles.back().setStructure(textureRepo.getTexture(Bush));
            } else if (structureType == "DeadBush") {
                tiles.back().setStructure(textureRepo.getTexture(DeadBush));
            } else if (structureType == "DeadGuy") {
                tiles.back().setStructure(textureRepo.getTexture(DeadGuy));
            } else if (structureType == "DeadTree") {
                tiles.back().setStructure(textureRepo.getTexture(DeadTree));
            } else if (structureType == "FatTree") {
                tiles.back().setStructure(textureRepo.getTexture(FatTree));
            } else if (structureType == "HangedGuy") {
                tiles.back().setStructure(textureRepo.getTexture(HangedGuy));
            } else if (structureType == "House1") {
                tiles.back().setStructure(textureRepo.getTexture(House1));
            } else if (structureType == "House2") {
                tiles.back().setStructure(textureRepo.getTexture(House2));
            } else if (structureType == "House3") {
                tiles.back().setStructure(textureRepo.getTexture(House3));
            } else if (structureType == "LongTree") {
                tiles.back().setStructure(textureRepo.getTexture(LongTree));
            } else if (structureType == "PalmTree") {
                tiles.back().setStructure(textureRepo.getTexture(PalmTree));
            } else if (structureType == "RipStone") {
                tiles.back().setStructure(textureRepo.getTexture(RipStone));
            } else if (structureType == "Tree") {
                tiles.back().setStructure(textureRepo.getTexture(Tree));
            } else if (structureType == "VeryDeadGuy") {
                tiles.back().setStructure(textureRepo.getTexture(VeryDeadGuy));
            } else if (structureType == "SunkenColumn") {
                tiles.back().setStructure(textureRepo.getTexture(SunkenColumn));
            } else if (structureType == "SunkenShip") {
                tiles.back().setStructure(textureRepo.getTexture(SunkenShip));
            }
        }
    }
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
    for (int i = 0; i < (VISIBLE_VERTICAL_TILES + 3); ++i) {
        for (int j = 0; j < (VISIBLE_HORIZONTAL_TILES + 3); ++j) {
            float x = (float)camera.x + (float)j * TILE_WIDTH;
            float y = (float)camera.y + (float)i * TILE_HEIGHT;
            if (x >= LEVEL_WIDTH) continue;
            if (y >= LEVEL_HEIGHT) continue;
            int xTile = floor(x / TILE_WIDTH);
            int yTile = floor(y / TILE_HEIGHT);
            int tile = yTile*TOTAL_HORIZONTAL_TILES + xTile;
            tiles[tile].renderStructure(camera);
        }
    }
}
