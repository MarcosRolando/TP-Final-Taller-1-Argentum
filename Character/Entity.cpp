//
// Created by marcos on 6/9/20.
//

#include "Entity.h"
#include "../GameConstants.h"

const unsigned int TILE_DISTANCE_IN_METERS = 2000;
const float SERVER_UPDATE_TIME = 33.f; /*in miliseconds*/

Entity::Entity(SDL_Rect &camera, float x, float y) : camera(camera) {
    currentFrame = 0;
    moveDirection = GameType::DIRECTION_STILL;
    lastDirection = GameType::DIRECTION_STILL;
    xPosition = x;
    yPosition = y;
    width = (float)TILE_WIDTH/2;
    height = (float)TILE_HEIGHT;
}

void Entity::_updateFrame(bool reachedDestination) {
    if (reachedDestination) {
        if (totalDistanceMoved < static_cast<float>(TILE_WIDTH)) {
            _modifyPosition(moveDirection, static_cast<float>(TILE_WIDTH) - totalDistanceMoved);
            totalDistanceMoved = static_cast<float>(TILE_WIDTH);
        }
        currentFrame = 0;
        lastDirection = moveDirection;
        moveDirection = GameType::DIRECTION_STILL;
        totalDistanceMoved = 0;
    } else {
        for (int i = 0; i < 6; ++i) { /*6 es la cantidad de frames distintos del body*/
            if (totalDistanceMoved < ((float)TILE_WIDTH/6 * (float)(i+1))) {
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
            case GameType::DIRECTION_UP:
                eTexture.renderBack((int)(xPosition) - camera.x,
                                    (int)(yPosition) - camera.y, currentFrame);
                break;
            case GameType::DIRECTION_DOWN:
                eTexture.renderFront((int)(xPosition) - camera.x,
                                     (int)(yPosition) - camera.y, currentFrame);
                break;
            case GameType::DIRECTION_RIGHT:
                eTexture.renderRight((int)(xPosition) - camera.x,
                                     (int)(yPosition) - camera.y, currentFrame);
                break;
            case GameType::DIRECTION_LEFT:
                eTexture.renderLeft((int)(xPosition) - camera.x,
                                    (int)(yPosition) - camera.y, currentFrame);
                break;
            case GameType::DIRECTION_STILL:
                _renderLastDirection(eTexture);
        }
    };
}

void Entity::_renderLastDirection(EntityTexture& eTexture) {
    switch (lastDirection) {
        case GameType::DIRECTION_UP:
            eTexture.renderBack((int)(xPosition) - camera.x,
                                (int)(yPosition) - camera.y, 0);
            break;
        case GameType::DIRECTION_DOWN:
            eTexture.renderFront((int)(xPosition) - camera.x,
                                 (int)(yPosition) - camera.y, 0);
            break;
        case GameType::DIRECTION_RIGHT:
            eTexture.renderRight((int)(xPosition) - camera.x,
                                 (int)(yPosition) - camera.y, 0);
            break;
        case GameType::DIRECTION_LEFT:
            eTexture.renderLeft((int)(xPosition) - camera.x,
                                (int)(yPosition) - camera.y, 0);
            break;
        case GameType::DIRECTION_STILL:
            eTexture.renderFront((int)(xPosition) - camera.x,
                                 (int)(yPosition) - camera.y, 0);
    }
}

void Entity::updateCamera() {
    //Center the camera over the entity
    camera.x = ((int)xPosition + 55 / 2 ) - DEFAULT_MAP_WIDTH / 2;
    camera.y = ((int)yPosition + 100 / 2 ) - DEFAULT_MAP_HEIGHT / 2;

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

void Entity::move(GameType::Direction direction, unsigned int distanceTravelled,
                  bool reachedDestination) {
    float distanceInPixels = static_cast<float>(TILE_WIDTH) *
                           static_cast<float>(distanceTravelled) / static_cast<float>(TILE_DISTANCE_IN_METERS);
    moveDirection = direction;
    _modifyPosition(direction, distanceInPixels);
    totalDistanceMoved += distanceInPixels;
    _updateFrame(reachedDestination);
}

void Entity::_modifyPosition(GameType::Direction direction, float distance) {
    switch (direction) {
        case GameType::DIRECTION_UP:
            yPosition -= distance;
            break;
        case GameType::DIRECTION_DOWN:
            yPosition += distance;
            break;
        case GameType::DIRECTION_LEFT:
            xPosition -= distance;
            break;
        case GameType::DIRECTION_RIGHT:
            xPosition += distance;
            break;
        case GameType::DIRECTION_STILL:
            //do nothing
            break;
    }
}

bool Entity::finishedMoving() const {
    return (moveDirection == GameType::DIRECTION_STILL);
}

void Entity::activateCamera() {
    cameraFollows = true;
}