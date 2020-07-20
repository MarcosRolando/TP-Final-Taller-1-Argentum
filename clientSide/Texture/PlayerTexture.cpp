//
// Created by marcos on 6/6/20.
//

#include "PlayerTexture.h"
#include "../Client/GameConstants.h"

PlayerTexture::PlayerTexture(TextureRepository& repo, PlayerEquipment equipment,
                            std::string&& _level) :textureRepo(repo),
                            textFont("/var/Argentum/Assets/Fonts/Raleway-Medium.ttf", 20),
                            level(textFont, repo.getRenderer(), std::move(_level)) {

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
    EntityTexture::render(head, x + 45, y + 15, 0);
    EntityTexture::render(body, x + 37, y + 30, frame);
    EntityTexture::render(helmet, x + 45, y + 15, 0);
    EntityTexture::render(shield, x + 52, y + 30, frame);
    EntityTexture::render(weapon, x + 37, y + 15, frame);
    level.render(x + TILE_WIDTH/2 - 10, y + TILE_HEIGHT - 20);
}

void PlayerTexture::renderBack(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(head, x + 45, y + 15, 3);
    EntityTexture::render(weapon, x + 40, y + 20, frame + 6);
    EntityTexture::render(shield, x + 37, y + 15, frame + 6);
    EntityTexture::render(body, x + 37, y + 30, frame + 6);
    EntityTexture::render(helmet, x + 45, y + 11, 3);
    level.render(x + TILE_WIDTH/2 - 10, y + TILE_HEIGHT - 20);
}

void PlayerTexture::renderRight(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(head, x + 46, y + 15, 1);
    EntityTexture::render(shield, x + 40, y + 30, frame + 18);
    EntityTexture::render(body, x + 37, y + 30, frame + 18);
    EntityTexture::render(helmet, x + 45, y + 11, 1);
    EntityTexture::render(weapon, x + 37, y + 20, frame + 18);
    level.render(x + TILE_WIDTH/2 - 10, y + TILE_HEIGHT - 20);
}

void PlayerTexture::renderLeft(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(head, x + 43, y + 15, 2);
    EntityTexture::render(weapon, x + 33, y + 20, frame + 12);
    EntityTexture::render(body, x + 37, y + 30, frame + 12);
    EntityTexture::render(helmet, x + 43, y + 11, 2);
    EntityTexture::render(shield, x + 47, y + 30, frame + 12);
    level.render(x + TILE_WIDTH/2 - 10, y + TILE_HEIGHT - 20);
}

void PlayerTexture::setLevel(const std::string &_level) {
    *(level.updateText(_level));
}

void PlayerTexture::equip(GameType::EquipmentPlace place, TextureID equipment) {
    Texture* texture = nullptr;
    if (equipment != Nothing) {
        texture = &textureRepo.getTexture(equipment);
    }
    switch (place) {
        case GameType::EQUIPMENT_PLACE_HEAD:
            helmet = texture;
            break;
        case GameType::EQUIPMENT_PLACE_CHEST:
            body = texture;
            break;
        case GameType::EQUIPMENT_PLACE_SHIELD:
            shield = texture;
            break;
        case GameType::EQUIPMENT_PLACE_WEAPON:
            weapon = texture;
            break;
        default:
            //do nothing
            break;
    }
}

