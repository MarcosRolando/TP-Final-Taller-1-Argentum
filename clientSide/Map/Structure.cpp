//
// Created by marcos on 10/6/20.
//

#include "Structure.h"
#include "../Client/GameConstants.h"
#include "../Miscellaneous/CameraCollisionVerifier.h"

Structure::Structure(Coordinate position, Texture* sTexture) : sTexture(sTexture) {
    if (sTexture != nullptr) {
        SpriteDimensions_t dimensions = sTexture->getSpriteDimensions();
        box = {position.j*TILE_WIDTH, position.i*TILE_HEIGHT, dimensions.width, dimensions.height};
    } else {
        box = {position.j*TILE_WIDTH, position.i*TILE_HEIGHT, 0, 0};
    }
}

void Structure::render(SDL_Rect& camera) {
    //Si se ve el tile en la pantalla
    if (sTexture != nullptr && CameraCollisionVerifier::isInsideCamera(camera, box, TILE_HEIGHT/2)) {
        sTexture->render(box.x - camera.x, box.y - camera.y);
    }
}

void Structure::setTexture(Texture& texture) {
    sTexture = &texture;
    SpriteDimensions_t dimensions = sTexture->getSpriteDimensions();
    box.w = dimensions.width;
    box.h = dimensions.height;
}
