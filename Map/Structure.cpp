//
// Created by marcos on 10/6/20.
//

#include "Structure.h"
#include "../GameConstants.h"

Structure::Structure(int x, int y, Texture *sTexture) : sTexture(sTexture) {
    box = {x, y, TILE_WIDTH, TILE_HEIGHT};
}

bool Structure::_checkCollision(SDL_Rect a, SDL_Rect b) {
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

void Structure::render(SDL_Rect& camera) {
    //If the tile is on screen
    if (_checkCollision(camera, box) && sTexture != nullptr) {
        //Show the tile
        sTexture->render(box.x - camera.x, box.y - camera.y);
    }
}

SDL_Rect Structure::getBox() const {
    return box;
}
