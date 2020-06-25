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
#include "../Character/NPC.h"

class Map {
private:
    TextureRepository& textureRepo;
    std::vector<Tile> tiles;
    SDL_Rect& camera;
    std::vector<NPC> npcs;

public:
    Map(TextureRepository& repo, SDL_Rect& camera);
    void renderGround();
    void renderStructures();
    void renderNPCS(float timeStep);
    void setSize(int rows, int columns);

private:
    void _setTiles();
};


#endif //ARGENTUM_MAP_H
