//
// Created by marcos on 6/7/20.
//

#include "Player.h"

Player::Player(TextureRepository& repo, SDL_Rect& camera, float x, float y, PlayerEquipment& images) :
        Entity(camera, x, y), pTexture(repo, images), ghostTexture(repo, PlayerGhost) {}

void Player::render(float timeStep) {
    Entity::updatePosition(timeStep);
    Entity::updateCamera();
    if (!isDead) {
        Entity::render(pTexture);
    } else {
        Entity::render(ghostTexture);
    }
}