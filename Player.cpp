//
// Created by marcos on 6/7/20.
//

#include "Player.h"

const int PLAYER_SPEED = 10;

Player::Player(SDL_Renderer& renderer, int x, int y, EquipmentImages& images) :
        pTexture(renderer, images) {

    ySpeed = 0;
    xSpeed = 0;
    xPosition = x;
    yPosition = y;
}

void Player::move() {
    xPosition += xSpeed;
    yPosition += ySpeed;
}

void Player::render() {
    pTexture.renderFront(xPosition, yPosition, 0);
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
