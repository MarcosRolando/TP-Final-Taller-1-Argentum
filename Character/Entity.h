//
// Created by marcos on 6/9/20.
//

#ifndef ARGENTUM_ENTITY_H
#define ARGENTUM_ENTITY_H

#include "../Texture/EntityTexture.h"
#include "../Timer.h"
#include "../Direction.h"

/*Clase Abstracta*/

class Entity {
private:
    Timer moveTime;
    SDL_Rect& camera;
    float movedOffset;
    int currentFrame;
    Direction moveDirection;
    float xPosition;
    float yPosition;

public:
    Entity(SDL_Rect& camera, float x, float y);
    void move(Direction direction);
    void render(EntityTexture& eTexture);
    virtual void render() = 0;
    void updatePosition();
    void updateCamera();
};


#endif //ARGENTUM_ENTITY_H
