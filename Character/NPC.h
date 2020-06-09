//
// Created by marcos on 6/8/20.
//

#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H

#include "../Texture/NPCTexture.h"
#include "../Timer.h"
#include "../Direction.h"

class NPC {
private:
    NPCTexture npcTexture;
    Timer moveTime;
    SDL_Rect& camera;
    float movedOffset;
    int currentFrame;
    Direction moveDirection;
    float xPosition;
    float yPosition;

public:
    NPC(SDL_Renderer& renderer, SDL_Rect& camera, float x, float y,
                                                        std::string image);
    void move(Direction direction);
    void render();

private:
    void _updatePosition();
};


#endif //ARGENTUM_NPC_H
