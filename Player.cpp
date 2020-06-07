//
// Created by marcos on 6/7/20.
//

#include "Player.h"

const int PLAYER_SPEED = 640;

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

Player::Player(SDL_Renderer& renderer, SDL_Rect& camera, float x, float y, EquipmentImages& images) :
        pTexture(renderer, images), camera(camera) {

    movedOffset = 0;
    currentFrame = 0;
    moveDirection = STILL;
    xPosition = x;
    yPosition = y;
}

void Player::move(float timeStep) {
    float offset = PLAYER_SPEED*timeStep;
    if (moveDirection != STILL) {
        if ( (movedOffset + offset) >= 160) {
            offset = 160 - movedOffset;
        }
        movedOffset += offset;
        ++currentFrame;
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
    if (movedOffset == 160) {
        currentFrame = 0;
        moveDirection = STILL;
        movedOffset = 0;
    } else if (movedOffset < 27.66) {
        currentFrame = 0;
    } else if (movedOffset < 53.33) {
        currentFrame = 1;
    } else if (movedOffset < 80.f) {
        currentFrame = 2;
    } else if (movedOffset < 107.66) {
        currentFrame = 3;
    } else if (movedOffset < 135.32) {
        currentFrame = 4;
    } else if (movedOffset < 162.98) {
        currentFrame = 5;
    }
}

void Player::render() {
    switch (moveDirection) {
        case UP:
            pTexture.renderBack((int)(xPosition) - camera.x,
                    (int)(yPosition) - camera.y, currentFrame);
            break;
        case DOWN:
            pTexture.renderFront((int)(xPosition) - camera.x,
                    (int)(yPosition) - camera.y, currentFrame);
            break;
        case RIGHT:
            pTexture.renderRight((int)(xPosition) - camera.x,
                    (int)(yPosition) - camera.y, currentFrame);
            break;
        case LEFT:
            pTexture.renderLeft((int)(xPosition) - camera.x,
                    (int)(yPosition) - camera.y, currentFrame);
            break;
        case STILL:
            pTexture.renderFront((int)(xPosition) - camera.x,
                    (int)(yPosition) - camera.y, 0);
            break;
    }
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && moveDirection == STILL) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: moveDirection = UP; break;
            case SDLK_DOWN: moveDirection = DOWN; break;
            case SDLK_LEFT: moveDirection = LEFT; break;
            case SDLK_RIGHT: moveDirection = RIGHT; break;
        }
    }
}

void Player::setCamera() {
    //Center the camera over the player
    camera.x = ((int)xPosition + 25 / 2 ) - 1280 / 2;
    camera.y = ((int)yPosition + 45 / 2 ) - 720 / 2;

    //Keep the camera in bounds
    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > LEVEL_WIDTH*2 - camera.w) { /*El *2 es por la escala de los tiles, ARREGLAR QUE NO SEA TAN CACA*/
        camera.x = LEVEL_WIDTH*2 - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT*2 - camera.h) {
        camera.y = LEVEL_HEIGHT*2 - camera.h;
    }
}
