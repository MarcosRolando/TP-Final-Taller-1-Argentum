//
// Created by marcos on 6/13/20.
//

#include "ItemDrop.h"

ItemDrop::ItemDrop(int x, int y) : sTexture(nullptr) {
    box = {x, y, 0, 0};
}

void ItemDrop::render(SDL_Rect& camera) {
    //If the tile is on screen
    if (sTexture != nullptr) {
        sTexture->render(box.x - camera.x, box.y - camera.y, 0, -90);
    }
}

void ItemDrop::setItem(Texture& itemTexture) {
    SpriteDimensions_t dimensions = itemTexture.getSpriteDimensions();
    box.w = dimensions.witdth;
    box.h = dimensions.height;
    sTexture = &itemTexture;
}
