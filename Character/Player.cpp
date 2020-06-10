//
// Created by marcos on 6/7/20.
//

#include "Player.h"
#include "../GameConstants.h"

Player::Player(TextureRepository& repo, SDL_Rect& camera, float x, float y, PlayerEquipment& images) :
        Entity(camera, x, y), pTexture(repo, images) {}

void Player::render() {
    Entity::updatePosition();
    Entity::updateCamera();
    Entity::render(pTexture);
}