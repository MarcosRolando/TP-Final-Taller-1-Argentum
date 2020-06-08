//
// Created by marcos on 6/7/20.
//

#include "Player.h"
#include "GameConstants.h"

const int PLAYER_SPEED = 50;

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
        if ( (movedOffset + offset) >= TILE_WIDTH*2/*tileScale*/) {
            offset = TILE_WIDTH*2 - movedOffset;
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
    for (int i = 0; i < 6; ++i) { /*6 es la cantidad de frames distintos del body*/
        if (movedOffset < ((float)TILE_WIDTH*2/6 * (float)(i+1)) && movedOffset < TILE_WIDTH*2) {
            currentFrame = i;
            break;
        }
        if (i == 5) {
            currentFrame = 0;
            moveDirection = STILL;
            movedOffset = 0;
        }
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
