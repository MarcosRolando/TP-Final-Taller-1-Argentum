//
// Created by marcos on 6/8/20.
//

#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H

#include "../Texture/NPCTexture.h"
#include "Entity.h"

class NPC : public Entity {
private:
    NPCTexture npcTexture;

public:
    NPC(SDL_Renderer& renderer, SDL_Rect& camera, float x, float y,
                                                        std::string image);
    void render() override;
};


#endif //ARGENTUM_NPC_H
