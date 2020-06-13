//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_TILE_H
#define ARGENTUM_TILE_H

#include "../Texture/Texture.h"
#include "ItemDrop.h"

class Tile {
private:
    //The attributes of the tile
    SDL_Rect box{};
    Texture& tileTexture;
    ItemDrop item;
    //The tile type
    int type;

public:
    //Initializes position and type
    Tile(int x, int y, int tileType, Texture& tileTexture);

    //Shows the tile
    void render(SDL_Rect& camera);

    void addItemDrop(Texture& itemTexture);
};


#endif //ARGENTUM_TILE_H
