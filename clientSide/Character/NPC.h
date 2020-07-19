//
// Created by marcos on 6/8/20.
//

#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H

#include "../Texture/NPCTexture.h"
#include "Entity.h"

/*Esta clase representa tanto a los monstruos como a los citizen (priest, banker, etc)*/

class NPC : public Entity {
private:
    NPCTexture npcTexture;

public:
    NPC(TextureRepository& repo, SDL_Rect& camera, float x, float y,
                                                        TextureID texture);

    /*Renderiza en el mapa al NPC*/
    void render() override;
};


#endif //ARGENTUM_NPC_H
