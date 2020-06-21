//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_GAMECONSTANTS_H
#define ARGENTUM_GAMECONSTANTS_H

//The dimensions of the tiles
const int TILE_WIDTH = 128;
const int TILE_HEIGHT = 128;

const int TOTAL_HORIZONTAL_TILES = 100;
const int TOTAL_VERTICAL_TILES = 100;
const int TOTAL_TILES = TOTAL_HORIZONTAL_TILES*TOTAL_VERTICAL_TILES;

const int VISIBLE_HORIZONTAL_TILES = 8;
const int VISIBLE_VERTICAL_TILES = 5;

//Map Viewport
const int DEFAULT_MAP_WIDTH = TILE_WIDTH*VISIBLE_HORIZONTAL_TILES;
const int DEFAULT_MAP_HEIGHT = TILE_HEIGHT*VISIBLE_VERTICAL_TILES;

//UI Viewport
const int DEFAULT_INVENTORY_WIDTH = 470;
const int DEFAULT_INVENTORY_HEIGHT = DEFAULT_MAP_HEIGHT + 296;

//Minichat Viewport
const int DEFAULT_MINICHAT_WIDTH = DEFAULT_MAP_WIDTH + 5;
const int DEFAULT_MINICHAT_HEIGHT = 210;

//PlayerInfo Viewport
const int DEFAULT_PLAYER_INFO_WIDTH = DEFAULT_MAP_WIDTH;
const int DEFAULT_PLAYER_INFO_HEIGHT = 45;

//Screen base constants
const int DEFAULT_SCREEN_WIDTH = DEFAULT_MAP_WIDTH + DEFAULT_INVENTORY_WIDTH;
const int DEFAULT_SCREEN_HEIGHT = DEFAULT_MAP_HEIGHT + 296;//=INVENTORY_HEIGHT

//General para todas las barras
const int BAR_HEIGHT = 30;

//Barras individuales
const int HEALTH_BAR_X_OFFSET = 25;
const int MANA_BAR_X_OFFSET = 385;
const int XP_BAR_X_OFFSET = 725;

//The dimensions of the level
const int LEVEL_WIDTH = TOTAL_HORIZONTAL_TILES * TILE_WIDTH;
const int LEVEL_HEIGHT = TOTAL_VERTICAL_TILES * TILE_HEIGHT;

//La velocidad de las animaciones
const int SPEED = 400;

#endif //ARGENTUM_GAMECONSTANTS_H
