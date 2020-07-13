//
// Created by marcos on 6/13/20.
//

#include "Spell.h"
#include "../Client/GameConstants.h"

const float ANIMATION_TIME = 20000.f;
const int SPELL_SPEED = 30;

Spell::Spell(Texture& texture, SDL_Rect &camera, float x, float y) :
                                sTexture(texture), camera(camera) {
    currentFrame = 0;
    timePassed = 0;
    xPosition = x;
    yPosition = y;
    width = (float)TILE_WIDTH/2;
    height = (float)TILE_HEIGHT/2 + 15;
}

void Spell::updateFrame(float timeStep) {
    //Calculate time step
    float offset = SPELL_SPEED*timeStep;
    if ( (timePassed + offset) >= ANIMATION_TIME) {
        timePassed = ANIMATION_TIME;
    } else {
        timePassed += offset;
    }
    if (timePassed >= ANIMATION_TIME) {
        currentFrame = 0;
        timePassed = 0;
        finished = true;
    } else {
        for (int i = 0; i < 24; ++i) { /*6 es la cantidad de frames distintos del spell*/
            if (timePassed < ((float)ANIMATION_TIME/24 * (float)(i+1))) {
                currentFrame = i;
                break;
            }
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

void Spell::render() {
    if (_checkCollision(camera, {(int)xPosition, (int)yPosition, (int)width, (int)height})) {
        sTexture.render((int)(xPosition) - camera.x,
                                (int)(yPosition) - camera.y, currentFrame);
    };
}

bool Spell::finishedAnimation() const {
    return finished;
}

void Spell::updatePosition(float x, float y) {
    xPosition = x;
    yPosition = y;
}
