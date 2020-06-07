//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_TILE_H
#define ARGENTUM_TILE_H

#include "Texture.h"

const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;

class Tile {
private:
    //The attributes of the tile
    SDL_Rect box{};
    Texture& tileTexture;
    //The tile type
    int type;

public:
    //Initializes position and type
    Tile(int x, int y, int tileType, Texture& texture);

    //Shows the tile
    void render(SDL_Rect& camera);

    //Get the tile type
    int getType() const;

    //Get the collision box
    SDL_Rect getBox() const;

private:
    static bool _checkCollision(SDL_Rect a, SDL_Rect b);
};


#endif //ARGENTUM_TILE_H
