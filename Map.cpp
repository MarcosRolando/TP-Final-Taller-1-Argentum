//
// Created by marcos on 6/7/20.
//

#include "Map.h"
#include <fstream>
#include "SDLException.h"

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

Map::Map(SDL_Renderer& renderer, SDL_Rect camera) {
    this->camera = camera;
    _loadTilesTextures(renderer);
    _setTiles();
}

void Map::_loadTilesTextures(SDL_Renderer& renderer) {
    textures.emplace_back(renderer);
    textures.back().loadFromFile("../Images/Map/tiles.png", {0, 0xFF, 0xFF});
}

void Map::_setTiles() {
    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream mapFile( "lazy.map" );

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
                tiles.emplace_back(x, y, tileType, textures.back());
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

    textures.back().addSprite(0, 0, TILE_WIDTH, TILE_HEIGHT); /*RED*/
    textures.back().addSprite(0, 80, TILE_WIDTH, TILE_HEIGHT); /*GREEN*/
    textures.back().addSprite(0, 160, TILE_WIDTH, TILE_HEIGHT); /*BLUE*/
    textures.back().addSprite(160,80, TILE_WIDTH, TILE_HEIGHT); /*CENTER*/
    textures.back().addSprite(160, 0, TILE_WIDTH, TILE_HEIGHT); /*TOP*/
    textures.back().addSprite(240, 0, TILE_WIDTH, TILE_HEIGHT); /*TOPRIGHT*/
    textures.back().addSprite(240, 80, TILE_WIDTH, TILE_HEIGHT); /*RIGTH*/
    textures.back().addSprite(240, 160, TILE_WIDTH, TILE_HEIGHT); /*BOTTOMRIGHT*/
    textures.back().addSprite(160, 160, TILE_WIDTH, TILE_HEIGHT); /*BOTTOM*/
    textures.back().addSprite(80, 160, TILE_WIDTH, TILE_HEIGHT); /*BOTTOMLEFT*/
    textures.back().addSprite(80, 80, TILE_WIDTH, TILE_HEIGHT); /*LEFT*/
    textures.back().addSprite(80, 0, TILE_WIDTH, TILE_HEIGHT); /*TOPLEFT*/

    //Close the file
    mapFile.close();
}

void Map::render() {

}
