//
// Created by marcos on 6/9/20.
//

#include "Entity.h"
#include "../GameConstants.h"

Entity::Entity(SDL_Rect &camera, float x, float y) : camera(camera) {

    movedOffset = 0;
    currentFrame = 0;
    moveDirection = STILL;
    xPosition = x;
    yPosition = y;
}

void Entity::updatePosition() {
    //Calculate time step
    float timeStep = moveTime.getTicks() / 1000.f;
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

void Entity::render(EntityTexture& eTexture) {
    moveTime.start(); //reseteo
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
            eTexture.renderFront((int)(xPosition) - camera.x,
                                   (int)(yPosition) - camera.y, 0);
            break;
    }
}

void Entity::updateCamera() {
    //Center the camera over the entity
    camera.x = ((int)xPosition + 25 / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ((int)yPosition + 45 / 2 ) - SCREEN_HEIGHT / 2;

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