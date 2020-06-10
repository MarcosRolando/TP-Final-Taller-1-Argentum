//
// Created by marcos on 6/7/20.
//

#include "Player.h"

Player::Player(TextureRepository& repo, SDL_Rect& camera, float x, float y, PlayerEquipment& images) :
        Entity(camera, x, y), pTexture(repo, images) {}

void Player::render(float timeStep) {
    Entity::updatePosition(timeStep);
    Entity::updateCamera();
    Entity::render(pTexture);
}