//
// Created by marcos on 6/7/20.
//

#include "Player.h"

const int PLAYER_SPEED = 10;

Player::Player(SDL_Renderer& renderer, int x, int y, std::string& helmetImage,
        std::string& headImage, std::string& bodyImage, std::string& weaponImage) :
        pTexture(renderer, helmetImage, headImage, bodyImage, weaponImage) {

    ySpeed = 0;
    xSpeed = 0;
    xPosition = x;
    yPosition = y;
}

void Player::move(Direction direction) {
    switch (direction) {
        case UP:
            ySpeed += PLAYER_SPEED;
            break;
        case DOWN:
            ySpeed += PLAYER_SPEED;
            break;
        case LEFT:

            break;
        case RIGHT:

            break;
    }
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
