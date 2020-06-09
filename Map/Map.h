//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H

/*Guarda las texturas de los tiles (asi no guardo mas de una vez las texturas de
 * un tile) y guarda tiles*/

#include "Tile.h"
#include <vector>
#include <memory>

class Map {
private:
    std::vector<Tile> tiles;
    std::vector<std::unique_ptr<Texture>> textures;
    SDL_Rect& camera;

public:
    Map(SDL_Renderer& renderer, SDL_Rect& camera);
    void render();

private:
    void _setTiles();
    void _loadTilesTextures(SDL_Renderer& renderer);
};


#endif //ARGENTUM_MAP_H
