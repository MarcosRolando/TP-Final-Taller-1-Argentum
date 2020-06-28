//
// Created by marcos on 6/6/20.
//

#include "PlayerTexture.h"

PlayerTexture::PlayerTexture(TextureRepository& repo, PlayerEquipment equipment)
                                : textureRepo(repo) {
    if (equipment.helmet != Nothing) helmet = &textureRepo.getTexture(equipment.helmet);
    else helmet = nullptr;
    head = &textureRepo.getTexture(equipment.head);
    body = &textureRepo.getTexture(equipment.body);
    if (equipment.shield != Nothing) shield = &textureRepo.getTexture(equipment.shield);
    else shield = nullptr;
    if (equipment.weapon != Nothing) weapon = &textureRepo.getTexture(equipment.weapon);
    else weapon = nullptr;
}

void PlayerTexture::renderFront(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(head, x + 45, y + 20, 0);
    EntityTexture::render(body, x + 37, y + 35, frame);
    EntityTexture::render(helmet, x + 45, y + 20, 0);
    EntityTexture::render(shield, x + 52, y + 35, frame);
    EntityTexture::render(weapon, x + 37, y + 20, frame);
}

void PlayerTexture::renderBack(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(head, x + 45, y + 20, 3);
    EntityTexture::render(weapon, x + 40, y + 25, frame + 6);
    EntityTexture::render(shield, x + 37, y + 20, frame + 6);
    EntityTexture::render(body, x + 37, y + 35, frame + 6);
    EntityTexture::render(helmet, x + 45, y + 16, 3);
}

void PlayerTexture::renderRight(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(head, x + 46, y + 20, 1);
    EntityTexture::render(shield, x + 40, y + 35, frame + 18);
    EntityTexture::render(body, x + 37, y + 35, frame + 18);
    EntityTexture::render(helmet, x + 45, y + 16, 1);
    EntityTexture::render(weapon, x + 37, y + 25, frame + 18);
}

void PlayerTexture::renderLeft(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(head, x + 43, y + 20, 2);
    EntityTexture::render(weapon, x + 33, y + 25, frame + 12);
    EntityTexture::render(body, x + 37, y + 35, frame + 12);
    EntityTexture::render(helmet, x + 43, y + 16, 2);
    EntityTexture::render(shield, x + 47, y + 35, frame + 12);
}

