//
// Created by marcos on 6/13/20.
//

#include "ItemDrop.h"
#include "../Client/GameConstants.h"

ItemDrop::ItemDrop(Coordinate position) : sTexture(nullptr) {
    box = {position.j*TILE_WIDTH, position.i*TILE_HEIGHT, 0, 0};
}

void ItemDrop::render(SDL_Rect& camera) {
    if (sTexture != nullptr) {
        sTexture->render(box.x - camera.x, box.y - camera.y, 0, -90);
    }
}

void ItemDrop::setItem(Texture* itemTexture) {
    if (itemTexture != nullptr) {
        SpriteDimensions_t dimensions = itemTexture->getSpriteDimensions();
        box.w = dimensions.width;
        box.h = dimensions.height;
    }
    sTexture = itemTexture;
}
