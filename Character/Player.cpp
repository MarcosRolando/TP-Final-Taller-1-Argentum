//
// Created by marcos on 6/7/20.
//

#include "Player.h"
#include "../GameConstants.h"

Player::Player(SDL_Renderer& renderer, SDL_Rect& camera, float x, float y, EquipmentImages& images) :
        Entity(camera, x, y), pTexture(renderer, images) {}

void Player::render() {
    Entity::updatePosition();
    Entity::updateCamera();
    Entity::render(pTexture);
}