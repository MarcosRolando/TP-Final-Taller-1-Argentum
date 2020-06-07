//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H

#include "PlayerTexture.h"

class Player {
private:
    PlayerTexture pTexture;
    SDL_Rect& camera;
    int xSpeed;
    int ySpeed;
    int xPosition;
    int yPosition;

public:
    Player(SDL_Renderer& renderer, SDL_Rect& camera, int x, int y, EquipmentImages& images);

    void move();

    void handleEvent(SDL_Event& e);

    void render();

    void setCamera();
};


#endif //ARGENTUM_PLAYER_H
