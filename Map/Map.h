//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H

/*Guarda las texturas de los tiles (asi no guardo mas de una vez las texturas de
 * un tile) y guarda tiles*/

#include "Tile.h"
#include <vector>
#include "../Texture/TextureRepository.h"
#include "Structure.h"

class Map {
private:
    TextureRepository& textureRepo;
    std::vector<Tile> tiles;
    SDL_Rect& camera;

public:
    Map(TextureRepository& repo, SDL_Rect& camera);
    void renderGround();
    void renderStructures();

private:
    void _setTiles();
};


#endif //ARGENTUM_MAP_H
