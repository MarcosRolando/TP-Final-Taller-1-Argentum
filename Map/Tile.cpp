//
// Created by marcos on 6/7/20.
//

#include "Tile.h"
#include "../GameConstants.h"

Tile::Tile(int x, int y, int tileType, Texture& tileTexture, Texture* sTexture)
            : tileTexture(tileTexture), item(x, y), structure(x, y, sTexture) {
    box = {x, y, TILE_WIDTH, TILE_HEIGHT};
    //Get the tile type
    type = tileType;
}

void Tile::renderGround(SDL_Rect& camera) {
    //If the tile is on screen
    tileTexture.render(box.x - camera.x, box.y - camera.y, type);
    item.render(camera);
}

void Tile::addItemDrop(Texture& itemTexture) {
    item.setItem(itemTexture);
}

void Tile::setStructure(Texture& sTexture) {
    structure.setTexture(sTexture);
}

void Tile::renderStructure(SDL_Rect &camera) {
    structure.render(camera);
}
