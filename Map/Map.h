//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H

/*Guarda las texturas de los tiles (asi no guardo mas de una vez las texturas de
 * un tile) y guarda tiles*/

#include "Tile.h"
#include <vector>

class Map {
private:
    std::vector<Tile> tiles;
    std::vector<Texture> textures;
    SDL_Rect& camera;

public:
    Map(SDL_Renderer& renderer, SDL_Rect& camera);
    void render();

private:
    void _setTiles();
};


#endif //ARGENTUM_MAP_H
