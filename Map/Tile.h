//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_TILE_H
#define ARGENTUM_TILE_H

#include "../Texture/Texture.h"
#include "ItemDrop.h"
#include "Structure.h"

class Tile {
private:
    //The attributes of the tile
    SDL_Rect box{};
    Texture& tileTexture;
    ItemDrop item;
    Structure structure;
    //The tile type
    int type;

public:
    //Initializes position and type
    Tile(int x, int y, int tileType, Texture& tileTexture, Texture* sTexture = nullptr);

    void setStructure(Texture& sTexture);

    //Shows the tile
    void renderGround(SDL_Rect& camera);

    void renderStructure(SDL_Rect& camera);

    void addItemDrop(Texture& itemTexture);
};


#endif //ARGENTUM_TILE_H
