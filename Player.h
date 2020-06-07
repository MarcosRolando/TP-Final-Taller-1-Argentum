//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H

#include "PlayerTexture.h"
#include "Timer.h"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STILL
};

class Player {
private:
    PlayerTexture pTexture;
    SDL_Rect& camera;
    float movedOffset;
    int currentFrame;
    Direction moveDirection;
    float xPosition;
    float yPosition;

public:
    Player(SDL_Renderer& renderer, SDL_Rect& camera, float x, float y, EquipmentImages& images);

    void move(float timeStep);

    void handleEvent(SDL_Event& e);

    void render();

    void setCamera();
};


#endif //ARGENTUM_PLAYER_H
