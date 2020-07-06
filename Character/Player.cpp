//
// Created by marcos on 6/7/20.
//

#include "Player.h"

Player::Player(TextureRepository& repo, SDL_Rect& camera, float x, float y,
        PlayerEquipment& images ,bool _isAlive) :
        Entity(camera, x, y), pTexture(repo, images), ghostTexture(repo, PlayerGhost) {
    isAlive = _isAlive;
}

void Player::render() {
    if (cameraFollows) {
        Entity::updateCamera();
    }
    if (isAlive) {
        Entity::render(pTexture);
    } else {
        Entity::render(ghostTexture);
    }
}

void Player::equip(GameType::EquipmentPlace place, TextureID equipment) {
    pTexture.equip(place, equipment);
}

void Player::kill() {
    isAlive = false;
}
