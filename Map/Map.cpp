//
// Created by marcos on 6/7/20.
//

#include "Map.h"
#include <fstream>
#include "../SDLException.h"
#include "../GameConstants.h"

Map::Map(SDL_Renderer& renderer, SDL_Rect& camera) : camera(camera) {
    this->camera = camera;
    _loadTilesTextures(renderer);
    _setTiles();
}

void Map::_loadTilesTextures(SDL_Renderer& renderer) {
    textures.emplace_back(new Texture(renderer));
    textures.back()->loadFromFile("../Images/Map/Grass.png", {0, 0xFF, 0xFF});
    textures.emplace_back(new Texture(renderer));
    textures.back()->loadFromFile("../Images/Map/Rock.png", {0, 0xFF, 0xFF});
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
            if (( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES )) {
                tiles.emplace_back(x, y, 2, i % 2, *textures[i % 2]);
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

    textures[0]->addSprite(0, 0, TILE_WIDTH, TILE_HEIGHT); /*RED*/
    textures[1]->addSprite(0, 0, TILE_WIDTH, TILE_HEIGHT); /*RED*/

    //Close the file
    mapFile.close();
}

void Map::render() {
    for (auto & tile : tiles) {
        tile.render(camera);
    }
}
