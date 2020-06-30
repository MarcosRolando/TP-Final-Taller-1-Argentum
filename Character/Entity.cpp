//
// Created by marcos on 6/9/20.
//

#include "Entity.h"
#include "../GameConstants.h"

const unsigned int TILE_DISTANCE_IN_METERS = 2000;
const float SERVER_UPDATE_TIME = 33.f; /*in miliseconds*/

Entity::Entity(SDL_Rect &camera, float x, float y) : camera(camera) {
    currentDistanceMoved = 0;
    currentFrame = 0;
    moveDirection = GameType::DIRECTION_STILL;
    lastDirection = GameType::DIRECTION_STILL;
    xPosition = x;
    yPosition = y;
    width = (float)TILE_WIDTH/2;
    height = (float)TILE_HEIGHT/2 + 15;
}

void Entity::updatePosition(float timeStep) {
    float offset = distancePerMilisecond*timeStep; //Calculate distanced move, offset es un auxiliar
    if (moveDirection != GameType::DIRECTION_STILL) {
        if ( (currentDistanceMoved + offset) >= distanceToMove) {
            offset = distanceToMove - currentDistanceMoved;
            currentDistanceMoved = distanceToMove;
        } else {
            currentDistanceMoved += offset;
        }
        totalDistanceMoved += offset;
        _modifyPosition(moveDirection, offset);
    }
    if (totalDistanceMoved >= (TILE_WIDTH - 2)/*le pongo un poco menos por error de redondeo de float que nunca llego*/) {/*Reinicio la animacion*/
        _modifyPosition(moveDirection, TILE_WIDTH - totalDistanceMoved);
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

void Entity::move(GameType::Direction direction, unsigned int distanceTravelled) {
    /*
    if (distanceToMove > currentDistanceMoved) { //Esto es por si por algun motivo no llegue a interpolarlo a la posicion de destino a tiempo
        _modifyPosition(moveDirection, distanceToMove - currentDistanceMoved);
        totalDistanceMoved += (distanceToMove - currentDistanceMoved);
    }
    */
    currentDistanceMoved = 0;
    moveDirection = direction;
    distanceToMove = static_cast<float>(TILE_WIDTH) *
            static_cast<float>(distanceTravelled) / static_cast<float>(TILE_DISTANCE_IN_METERS);
    distancePerMilisecond = distanceToMove / SERVER_UPDATE_TIME;
    _modifyPosition(direction, distanceToMove);
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
