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

    ySpeed = 0;
    xSpeed = 0;
    xPosition = x;
    yPosition = y;
}

void Player::move(float timeStep) {
    xPosition += xSpeed*timeStep;
    yPosition += ySpeed*timeStep;
}

void Player::render() {
    pTexture.renderFront((int)(xPosition) - camera.x, (int)(yPosition) - camera.y, 0);
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Adjust the velocity
        switch(e.key.keysym.sym) {
            case SDLK_UP: ySpeed -= PLAYER_SPEED; break;
            case SDLK_DOWN: ySpeed += PLAYER_SPEED; break;
            case SDLK_LEFT: xSpeed -= PLAYER_SPEED; break;
            case SDLK_RIGHT: xSpeed += PLAYER_SPEED; break;
        }
    }
        //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        //Adjust the velocity
        switch(e.key.keysym.sym) {
            case SDLK_UP: ySpeed += PLAYER_SPEED; break;
            case SDLK_DOWN: ySpeed -= PLAYER_SPEED; break;
            case SDLK_LEFT: xSpeed += PLAYER_SPEED; break;
            case SDLK_RIGHT: xSpeed -= PLAYER_SPEED; break;
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
