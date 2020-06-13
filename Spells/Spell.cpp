//
// Created by marcos on 6/13/20.
//

#include "Spell.h"
#include "../GameConstants.h"

const float animationTime = 150.f;

Spell::Spell(Texture& texture, SDL_Rect &camera, float x, float y) :
                                sTexture(texture), camera(camera) {
    currentFrame = 0;
    timePassed = 0;
    xPosition = x;
    yPosition = y;
    width = (float)TILE_WIDTH/2;
    height = (float)TILE_HEIGHT/2 + 15;
}

void Spell::_updateFrame(float timeStep) {
    //Calculate time step
    float offset = SPEED*timeStep;
    if ( (timePassed + offset) >= animationTime) {
        timePassed = 150.f;
    } else {
        timePassed += offset;
    }
    for (int i = 0; i < 6; ++i) { /*6 es la cantidad de frames distintos del spell*/
        if (timePassed < ((float)animationTime/6 * (float)(i+1))) {
            currentFrame = i;
            break;
        }
    }
}

bool Spell::_checkCollision(SDL_Rect a, SDL_Rect b) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if(bottomA <= topB) return false;
    if(topA >= bottomB) return false;
    if(rightA <= leftB) return false;
    if(leftA >= rightB) return false;

    //If none of the sides from A are outside B
    return true;
}

void Spell::render(float timeStep) {
    _updateFrame(timeStep);
    if (_checkCollision(camera, {(int)xPosition, (int)yPosition, (int)width, (int)height})) {
        sTexture.render((int)(xPosition) - camera.x,
                            (int)(yPosition) - camera.y, currentFrame);
    };
}