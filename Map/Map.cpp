//
// Created by marcos on 6/7/20.
//

#include "Map.h"
#include <fstream>
#include "../GameConstants.h"

Map::Map(TextureRepository& repo, SDL_Rect& camera) : textureRepo(repo), camera(camera) {
    this->camera = camera;
    _setTiles();
}

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
            //Determines what kind of tile will be made
            //int tileType = -1;

            //Read tile from map file
            //mapFile >> tileType;

            //If the was a problem in reading the map
            if (mapFile.fail()) {
                //Stop loading map
                throw SDLException("Error loading map: Unexpected end of file!\n");
            }

            //If the number is a valid tile number
            tiles.emplace_back(x, y, i%4, textureRepo.getTexture(Grass));
            if (i == 40) structures.emplace_back(x, y, textureRepo.getTexture(BlueTunicDrop));
            /*
            if (tileType >= 0 ) {
                tiles.emplace_back(x, y, i%4, textureRepo.getTexture(Grass));
                if (i == 100) structures.emplace_back(x, y, textureRepo.getTexture(House3));
            } else {
                throw SDLException("Error loading map: Invalid tile type at %d!\n", i);
            }
            */
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
