//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_GAMECONSTANTS_H
#define ARGENTUM_GAMECONSTANTS_H

//The dimensions of the tiles
const int TILE_WIDTH = 128;
const int TILE_HEIGHT = 128;

const int TOTAL_HORIZONTAL_TILES = 12;
const int TOTAL_VERTICAL_TILES = 16;
const int TOTAL_TILES = TOTAL_HORIZONTAL_TILES*TOTAL_VERTICAL_TILES;

const int VISIBLE_HORIZONTAL_TILES = 9;
const int VISIBLE_VERTICAL_TILES = 6;

//Map Viewport
const int DEFAULT_MAP_WIDTH = TILE_WIDTH*VISIBLE_HORIZONTAL_TILES; /*1152*/
const int DEFAULT_MAP_HEIGHT = TILE_HEIGHT*VISIBLE_VERTICAL_TILES; /*768*/

//Inventory Viewport
const int DEFAULT_INVENTORY_WIDTH = 400;
const int DEFAULT_INVENTORY_HEIGHT = 768;

//MiniChat Viewport
const int DEFAULT_MINICHAT_WIDTH = DEFAULT_MAP_HEIGHT + DEFAULT_INVENTORY_WIDTH;
const int DEFAULT_MINICHAT_HEIGHT = 100;

//Screen base constants
const int DEFAULT_SCREEN_WIDTH = DEFAULT_MAP_WIDTH + DEFAULT_INVENTORY_WIDTH;
const int DEFAULT_SCREEN_HEIGHT = DEFAULT_MAP_HEIGHT + DEFAULT_MINICHAT_HEIGHT;

//General para todas las barras
const int BAR_WIDTH = 225;
const int BAR_HEIGHT = 35;
const int BAR_X_OFFSET = 90;

//Barras individuales
const int HEALTH_BAR_Y_OFFSET = 0;
const int MANA_BAR_Y_OFFSET = 45;
const int XP_BAR_Y_OFFSET = 90;

//The dimensions of the level
const int LEVEL_WIDTH = TOTAL_HORIZONTAL_TILES * TILE_WIDTH;
const int LEVEL_HEIGHT = TOTAL_VERTICAL_TILES * TILE_HEIGHT;

//La velocidad de las animaciones
const int SPEED = 400;

#endif //ARGENTUM_GAMECONSTANTS_H
