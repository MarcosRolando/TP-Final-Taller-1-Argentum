//
// Created by marcos on 6/7/20.
//

#include "Map.h"
#include <fstream>
#include "../GameConstants.h"

const int TOTAL_TILES = 192;

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
            int tileType = -1;

            //Read tile from map file
            mapFile >> tileType;

            //If the was a problem in reading the map
            if (mapFile.fail()) {
                //Stop loading map
                throw SDLException("Error loading map: Unexpected end of file!\n");
            }

            //If the number is a valid tile number
            if (tileType >= 0 ) {
                tiles.emplace_back(x, y, i%4, textureRepo.getTexture(Grass));
                if (i == 100) structures.emplace_back(x, y, textureRepo.getTexture(House1));
            } else {
                throw SDLException("Error loading map: Invalid tile type at %d!\n", i);
            }

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
    for (auto & tile : tiles) {
        tile.render(camera);
    }
}

void Map::renderStructures() {
    for (auto & structure : structures) {
        structure.render(camera);
    }
}
