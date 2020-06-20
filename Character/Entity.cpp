//
// Created by marcos on 6/9/20.
//

#include "Entity.h"
#include "../GameConstants.h"

Entity::Entity(SDL_Rect &camera, float x, float y) : camera(camera) {
    movedOffset = 0;
    currentFrame = 0;
    moveDirection = STILL;
    lastDirection = STILL;
    xPosition = x;
    yPosition = y;
    width = (float)TILE_WIDTH/2;
    height = (float)TILE_HEIGHT/2 + 15;
}

void Entity::updatePosition(float timeStep) {
    //Calculate time step
    float offset = SPEED*timeStep;
    if (moveDirection != STILL) {
        if ( (movedOffset + offset) >= (float)TILE_WIDTH) {
            offset = TILE_WIDTH - movedOffset;
            movedOffset = TILE_WIDTH;
        } else {
            movedOffset += offset;
        }
        switch (moveDirection) {
            case UP:
                yPosition -= offset;
                break;
            case DOWN:
                yPosition += offset;
                break;
            case RIGHT:
                xPosition += offset;
                break;
            case LEFT:
                xPosition -= offset;
                break;
            case STILL:
                //do nothing
                break;
        }
    }
    if (movedOffset >= TILE_WIDTH) {
        currentFrame = 0;
        lastDirection = moveDirection;
        moveDirection = STILL;
        movedOffset = 0;
    } else {
        for (int i = 0; i < 6; ++i) { /*6 es la cantidad de frames distintos del body*/
            if (movedOffset < ((float)TILE_WIDTH/6 * (float)(i+1))) {
                currentFrame = i;
                break;
            }
        }
    }
}

bool Entity::_checkCollision(SDL_Rect a, SDL_Rect b) {
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

void Entity::render(EntityTexture& eTexture) {
    if (_checkCollision(camera, {(int)xPosition, (int)yPosition, (int)width, (int)height})) {
        switch (moveDirection) {
            case UP:
                eTexture.renderBack((int)(xPosition) - camera.x,
                                    (int)(yPosition) - camera.y, currentFrame);
                break;
            case DOWN:
                eTexture.renderFront((int)(xPosition) - camera.x,
                                     (int)(yPosition) - camera.y, currentFrame);
                break;
            case RIGHT:
                eTexture.renderRight((int)(xPosition) - camera.x,
                                     (int)(yPosition) - camera.y, currentFrame);
                break;
            case LEFT:
                eTexture.renderLeft((int)(xPosition) - camera.x,
                                    (int)(yPosition) - camera.y, currentFrame);
                break;
            case STILL:
                _renderLastDirection(eTexture);
        }
    };
}

void Entity::_renderLastDirection(EntityTexture& eTexture) {
    switch (lastDirection) {
        case UP:
            eTexture.renderBack((int)(xPosition) - camera.x,
                                (int)(yPosition) - camera.y, 0);
            break;
        case DOWN:
            eTexture.renderFront((int)(xPosition) - camera.x,
                                 (int)(yPosition) - camera.y, 0);
            break;
        case RIGHT:
            eTexture.renderRight((int)(xPosition) - camera.x,
                                 (int)(yPosition) - camera.y, 0);
            break;
        case LEFT:
            eTexture.renderLeft((int)(xPosition) - camera.x,
                                (int)(yPosition) - camera.y, 0);
            break;
        case STILL:
            eTexture.renderFront((int)(xPosition) - camera.x,
                                 (int)(yPosition) - camera.y, 0);
    }
}

void Entity::updateCamera() {
    //Center the camera over the entity
    camera.x = ((int)xPosition + 25 / 2 ) - DEFAULT_MAP_WIDTH / 2;
    camera.y = ((int)yPosition + 45 / 2 ) - DEFAULT_MAP_HEIGHT / 2;

    //Keep the camera in bounds
    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > LEVEL_WIDTH - camera.w) {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h) {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

void Entity::move(Direction direction) {
    if (moveDirection == STILL) moveDirection = direction;
}

float Entity::getXPosition(){ //Estas capaz despues las tenemos q sacar, ahora
    // las uso para probar
    return xPosition;
}

float Entity::getYPosition(){
    return yPosition;
}