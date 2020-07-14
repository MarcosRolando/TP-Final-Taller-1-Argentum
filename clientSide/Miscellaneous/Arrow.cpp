//
// Created by marcos on 14/7/20.
//

#include "Arrow.h"
#include "../Client/GameConstants.h"

const int ARROW_SPEED = 30;

Arrow::Arrow(Texture& texture, SDL_Rect &camera, float xPos, float yPos,
                float xTarget, float yTarget) :
        sTexture(texture), camera(camera) {
    currDistance = 0;
    xPosition = xPos;
    yPosition = yPos;
    _calculateTrajectory(xTarget, yTarget);
    width = (float)TILE_WIDTH/2;
    height = (float)TILE_HEIGHT/2 + 15;
}

bool Arrow::_checkCollision(SDL_Rect a, SDL_Rect b) {
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

void Arrow::_calculateTrajectory(float xTarget, float yTarget) {
    float relativeXTarget = xTarget - xPosition; /*Lo llevo relativo al origen que es la posicion de mi flecha*/
    float relativeYTarget = yPosition - yTarget;
    angle = atan2(relativeYTarget, relativeXTarget) * 180 / M_PI; /*Calculo el angulo de la recta*/
    distanceToTravel = sqrt(pow(xTarget, 2.0) + pow(yTarget, 2.0));
}

void Arrow::render() {
    if (_checkCollision(camera, {(int)xPosition, (int)yPosition, (int)width, (int)height})) {
        sTexture.render((int)(xPosition) - camera.x,
                        (int)(yPosition) - camera.y, 0, angle - 120);
    };
}

void Arrow::update(double timeStep) {
    if (!finished) {
        float moved = ARROW_SPEED * timeStep;
        xPosition += moved * cos(angle);
        yPosition += moved * sin(angle);
        currDistance += moved;
        if (currDistance >= distanceToTravel) {
            finished = true;
        }
    }
}

bool Arrow::reachedTarget() const {
    return finished;
}
