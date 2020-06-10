//
// Created by marcos on 6/7/20.
//

#include "Tile.h"
#include "../GameConstants.h"

Tile::Tile(int x, int y, int tileType, Texture& texture)
            : tileTexture(texture) {
    box = {x, y, TILE_WIDTH, TILE_HEIGHT};
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
        tileTexture.render(box.x - camera.x, box.y - camera.y, type);
    }
}

int Tile::getType() const {
    return type;
}

SDL_Rect Tile::getBox() const {
    return box;
}