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
    MapFileReader mapFile("map.json");

    for (int j = 0; j < TOTAL_HORIZONTAL_TILES; ++j) {
        for (int i = 0; i < TOTAL_VERTICAL_TILES; ++i) {
            std::string tileType = mapFile.getTile(j, i);
            int x = i*TILE_WIDTH;
            int y = j*TILE_HEIGHT;
            if (tileType.find("DeadGrass") != (size_t )-1) {
                tiles.emplace_back(x, y, (int)tileType[9] - 48, textureRepo.getTexture(DeadGrass));
            } else if (tileType.find("Grass") != (size_t )-1) {
                tiles.emplace_back(x, y, (int)tileType[5] - 48, textureRepo.getTexture(Grass));
            } else if (tileType.find("Water") != (size_t )-1) {
                tiles.emplace_back(x, y, (int) tileType[5] - 48,textureRepo.getTexture(Water));
            } else if (tileType == "Sand") {
                tiles.emplace_back(x, y, 0,textureRepo.getTexture(Sand));
            } else {
                tiles.emplace_back(x, y, 0, textureRepo.getTexture(Water));
            }
            std::string structureType = mapFile.getStructure(j, i);
            if (structureType == "BoneGuy") {
                structures.emplace_back(x, y, textureRepo.getTexture(BoneGuy));
            } else if (structureType == "BrokenRipStone") {
                structures.emplace_back(x, y, textureRepo.getTexture(BrokenRipStone));
            } else if (structureType == "Bush") {
                structures.emplace_back(x, y, textureRepo.getTexture(Bush));
            } else if (structureType == "DeadBush") {
                structures.emplace_back(x, y, textureRepo.getTexture(DeadBush));
            } else if (structureType == "DeadGuy") {
                structures.emplace_back(x, y, textureRepo.getTexture(DeadGuy));
            } else if (structureType == "DeadTree") {
                structures.emplace_back(x, y, textureRepo.getTexture(DeadTree));
            } else if (structureType == "FatTree") {
                structures.emplace_back(x, y, textureRepo.getTexture(FatTree));
            } else if (structureType == "HangedGuy") {
                structures.emplace_back(x, y, textureRepo.getTexture(HangedGuy));
            } else if (structureType == "House1") {
                structures.emplace_back(x, y, textureRepo.getTexture(House1));
            } else if (structureType == "House2") {
                structures.emplace_back(x, y, textureRepo.getTexture(House2));
            } else if (structureType == "House3") {
                structures.emplace_back(x, y, textureRepo.getTexture(House3));
            } else if (structureType == "LongTree") {
                structures.emplace_back(x, y, textureRepo.getTexture(LongTree));
            } else if (structureType == "PalmTree") {
                structures.emplace_back(x, y, textureRepo.getTexture(PalmTree));
            } else if (structureType == "RipStone") {
                structures.emplace_back(x, y, textureRepo.getTexture(RipStone));
            } else if (structureType == "Tree") {
                structures.emplace_back(x, y, textureRepo.getTexture(Tree));
            } else if (structureType == "VeryDeadGuy") {
                structures.emplace_back(x, y, textureRepo.getTexture(VeryDeadGuy));
            }
        }
    }
}

/*
void Map::_setTiles() {
    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream mapFile( "../lazy.map" );

    //If the map couldn't be loaded
    if (mapFile.fail()) {
        throw SDLException("Unable to load map file!\n");
    } else {
        //Initialize the tiles
        for (int i = 0; i < TOTAL_TILES; ++i) {
            //If the was a problem in reading the map
            if (mapFile.fail()) {
                //Stop loading map
                throw SDLException("Error loading map: Unexpected end of file!\n");
            }

            //If the number is a valid tile number
            tiles.emplace_back(x, y, i%4, textureRepo.getTexture(Grass));
            if (i == 25) structures.emplace_back(x, y, textureRepo.getTexture(VeryDeadGuy));
            if (i == 5) tiles[5].addItemDrop(textureRepo.getTexture(GnarledStaffDrop));

            //Move to next tile spot
            x += TILE_WIDTH;

            //If we've gone too far
            if (x >= LEVEL_WIDTH) {
                //Move back
                x = 0;
                //Move to the next row
                y += TILE_HEIGHT;
            }
        }
    }

    //Close the file
    mapFile.close();
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
            tiles[tile].render(camera);
        }
    }
}

void Map::renderStructures() {
    for (auto & structure : structures) {
        structure.render(camera);
    }
}
