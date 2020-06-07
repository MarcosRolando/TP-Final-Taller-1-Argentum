//
// Created by marcos on 6/7/20.
//

#include "Tile.h"

//The different tile sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

Tile::Tile(int x, int y, int scale, int tileType, Texture& texture)
            : tileTexture(texture) {
    this->scale = scale;
    box = {x*scale, y*scale, TILE_WIDTH, TILE_HEIGHT}; /*Editando x e y puedo cambiar el tamanio de los bloques*/
    //Get the tile type
    type = tileType;
}

bool Tile::_checkCollision(SDL_Rect a, SDL_Rect b) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if(bottomA <= topB) return false;
    if(topA >= bottomB) return false;
    if(rightA <= leftB) return false;
    if(leftA >= rightB) return false;

    //If none of the sides from A are outside B
    return true;
}

void Tile::render(SDL_Rect& camera) {
    //If the tile is on screen
    if (_checkCollision(camera, box)) {
        //Show the tile
        tileTexture.render(box.x - camera.x, box.y - camera.y, type, scale);
    }
}

int Tile::getType() const {
    return type;
}

SDL_Rect Tile::getBox() const {
    return box;
}