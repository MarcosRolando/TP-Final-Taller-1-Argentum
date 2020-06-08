//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H

#include "PlayerTexture.h"
#include "Timer.h"
#include "Direction.h"

class Player {
private:
    PlayerTexture pTexture;
    Timer moveTime;
    SDL_Rect& camera;
    float movedOffset;
    int currentFrame;
    Direction moveDirection;
    float xPosition;
    float yPosition;

public:
    Player(SDL_Renderer& renderer, SDL_Rect& camera, float x, float y,
            EquipmentImages& images);

    void handleEvent(SDL_Event& e);

    void render();

private:
    void _updatePosition();
    void _updateCamera();
};


#endif //ARGENTUM_PLAYER_H
