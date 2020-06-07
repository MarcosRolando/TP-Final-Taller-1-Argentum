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

        gTileClips[ TILE_RED ].x = 0;
        gTileClips[ TILE_RED ].y = 0;
        gTileClips[ TILE_RED ].w = TILE_WIDTH;
        gTileClips[ TILE_RED ].h = TILE_HEIGHT;

        gTileClips[ TILE_GREEN ].x = 0;
        gTileClips[ TILE_GREEN ].y = 80;
        gTileClips[ TILE_GREEN ].w = TILE_WIDTH;
        gTileClips[ TILE_GREEN ].h = TILE_HEIGHT;

        gTileClips[ TILE_BLUE ].x = 0;
        gTileClips[ TILE_BLUE ].y = 160;
        gTileClips[ TILE_BLUE ].w = TILE_WIDTH;
        gTileClips[ TILE_BLUE ].h = TILE_HEIGHT;

        gTileClips[ TILE_TOPLEFT ].x = 80;
        gTileClips[ TILE_TOPLEFT ].y = 0;
        gTileClips[ TILE_TOPLEFT ].w = TILE_WIDTH;
        gTileClips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

        gTileClips[ TILE_LEFT ].x = 80;
        gTileClips[ TILE_LEFT ].y = 80;
        gTileClips[ TILE_LEFT ].w = TILE_WIDTH;
        gTileClips[ TILE_LEFT ].h = TILE_HEIGHT;

        gTileClips[ TILE_BOTTOMLEFT ].x = 80;
        gTileClips[ TILE_BOTTOMLEFT ].y = 160;
        gTileClips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
        gTileClips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;

        gTileClips[ TILE_TOP ].x = 160;
        gTileClips[ TILE_TOP ].y = 0;
        gTileClips[ TILE_TOP ].w = TILE_WIDTH;
        gTileClips[ TILE_TOP ].h = TILE_HEIGHT;

        gTileClips[ TILE_CENTER ].x = 160;
        gTileClips[ TILE_CENTER ].y = 80;
        gTileClips[ TILE_CENTER ].w = TILE_WIDTH;
        gTileClips[ TILE_CENTER ].h = TILE_HEIGHT;

        gTileClips[ TILE_BOTTOM ].x = 160;
        gTileClips[ TILE_BOTTOM ].y = 160;
        gTileClips[ TILE_BOTTOM ].w = TILE_WIDTH;
        gTileClips[ TILE_BOTTOM ].h = TILE_HEIGHT;

        gTileClips[ TILE_TOPRIGHT ].x = 240;
        gTileClips[ TILE_TOPRIGHT ].y = 0;
        gTileClips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
        gTileClips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;

        gTileClips[ TILE_RIGHT ].x = 240;
        gTileClips[ TILE_RIGHT ].y = 80;
        gTileClips[ TILE_RIGHT ].w = TILE_WIDTH;
        gTileClips[ TILE_RIGHT ].h = TILE_HEIGHT;

        gTileClips[ TILE_BOTTOMRIGHT ].x = 240;
        gTileClips[ TILE_BOTTOMRIGHT ].y = 160;
        gTileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
        gTileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
    }

    //Close the file
    mapFile.close();
}
