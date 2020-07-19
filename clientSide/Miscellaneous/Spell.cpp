//
// Created by marcos on 6/13/20.
//

#include "Spell.h"
#include "../Client/GameConstants.h"
#include "../Miscellaneous/CameraCollisionVerifier.h"

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

void Spell::updateFrame(double timeStep) {
    //Calculo time step
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

void Spell::render() {
    if (CameraCollisionVerifier::isInsideCamera(camera, {(int)xPosition,
                                                         (int)yPosition, (int)width, (int)height})) {
        sTexture.render((int)(xPosition) - camera.x,
                                (int)(yPosition) - camera.y, currentFrame);
    };
}

bool Spell::finishedAnimation() const {
    return finished;
}

void Spell::setPosition(float x, float y) {
    xPosition = x;
    yPosition = y;
}
