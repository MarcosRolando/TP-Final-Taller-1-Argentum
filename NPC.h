//
// Created by marcos on 6/8/20.
//

#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H

#include "NPCTexture.h"
#include "Direction.h"

class NPC {
private:
    NPCTexture npcTexture;
    SDL_Rect& camera;
    float movedOffset;
    int currentFrame;
    Direction moveDirection;
    float xPosition;
    float yPosition;

public:
    NPC(SDL_Renderer& renderer, SDL_Rect& camera, float x, float y,
                                                        std::string image);
    void move(float timeStep);

    void render();
};


#endif //ARGENTUM_NPC_H
