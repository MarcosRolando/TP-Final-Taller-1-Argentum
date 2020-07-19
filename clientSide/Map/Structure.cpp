//
// Created by marcos on 10/6/20.
//

#include "Structure.h"
#include "../Client/GameConstants.h"

Structure::Structure(Coordinate position, Texture* sTexture) : sTexture(sTexture) {
    if (sTexture != nullptr) {
        SpriteDimensions_t dimensions = sTexture->getSpriteDimensions();
        box = {position.j*TILE_WIDTH, position.i*TILE_HEIGHT, dimensions.width, dimensions.height};
    } else {
        box = {position.j*TILE_WIDTH, position.i*TILE_HEIGHT, 0, 0};
    }
}

bool Structure::_checkCollision(SDL_Rect a, SDL_Rect b) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    //Calculo los lados de A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculo los lados de B
    leftB = b.x;
    rightB = b.x + b.w + TILE_WIDTH/2;
    topB = b.y  + TILE_HEIGHT/2 - b.h; /*NO ES IGUAL A LAS OTRAS, OJO!*/
    bottomB = b.y + TILE_HEIGHT/2; /*Porque centro las estructuras en el medio del tile*/

    //Si alguno de los lados de A esta fuera de B
    if(bottomA <= topB) return false;
    if(topA >= bottomB) return false;
    if(rightA <= leftB) return false;
    if(leftA >= rightB) return false;

    //    //Si ningun lado de A esta fuera de B
    return true;
}

void Structure::render(SDL_Rect& camera) {
    //Si se ve el tile en la pantalla
    if (sTexture != nullptr && _checkCollision(camera, box)) {
        sTexture->render(box.x - camera.x, box.y - camera.y);
    }
}

void Structure::setTexture(Texture& texture) {
    sTexture = &texture;
    SpriteDimensions_t dimensions = sTexture->getSpriteDimensions();
    box.w = dimensions.width;
    box.h = dimensions.height;
}
