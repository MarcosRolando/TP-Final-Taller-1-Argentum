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
    float xPosition, width;
    float yPosition, height;

public:
    Entity(SDL_Rect& camera, float x, float y);
    void move(Direction direction);
    void render(EntityTexture& eTexture);
    virtual void render() = 0;
    void updatePosition();
    void updateCamera();

private:
    static bool _checkCollision(SDL_Rect a, SDL_Rect b);
};


#endif //ARGENTUM_ENTITY_H
