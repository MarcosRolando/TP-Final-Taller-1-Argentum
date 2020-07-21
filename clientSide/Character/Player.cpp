//
// Created by marcos on 6/7/20.
//

#include "Player.h"

Player::Player(TextureRepository& repo, SDL_Rect& camera, float x, float y,
        PlayerEquipment& images, bool _isAlive, std::string&& level, const std::string& nickname) :
        Entity(camera, x, y), pTexture(repo, images, level, nickname),
        ghostTexture(repo, PlayerGhost, " (" + level + ")", nickname) {
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

void Player::revive() {
    isAlive = true;
}

void Player::updateLevel(int level) {
    std::string strLevel = std::to_string(level);
    pTexture.setLevel(strLevel);
    ghostTexture.setLevel(" (" + strLevel + ")");
}

