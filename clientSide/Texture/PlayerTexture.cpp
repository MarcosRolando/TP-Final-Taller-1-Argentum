//
// Created by marcos on 6/6/20.
//

#include "PlayerTexture.h"
#include "../Client/GameConstants.h"

PlayerTexture::PlayerTexture(TextureRepository& repo, PlayerEquipment equipment,
                            const std::string& _level, const std::string& _nickname) :textureRepo(repo),
                            textFont("/var/Argentum/Assets/Fonts/Raleway-Medium.ttf", 20),
                            nickname(textFont, repo.getRenderer(), _nickname),
                            level(textFont, repo.getRenderer(), " (" + _level + ")") {

    textLevelOffset = level.getTextTextureWidth();
    textNicknameOffset = (nickname.getTextTextureWidth() + textLevelOffset)/2;
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
    nickname.render(x + TILE_WIDTH/2 - textNicknameOffset, y + TILE_HEIGHT - 15);
    level.render(x + TILE_WIDTH/2 + textNicknameOffset - textLevelOffset, y + TILE_HEIGHT - 15);
}

void PlayerTexture::renderBack(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(head, x + 45, y + 15, 3);
    EntityTexture::render(weapon, x + 40, y + 20, frame + 6);
    EntityTexture::render(shield, x + 37, y + 15, frame + 6);
    EntityTexture::render(body, x + 37, y + 30, frame + 6);
    EntityTexture::render(helmet, x + 45, y + 11, 3);
    nickname.render(x + TILE_WIDTH/2 - textNicknameOffset, y + TILE_HEIGHT - 15);
    level.render(x + TILE_WIDTH/2 + textNicknameOffset - textLevelOffset, y + TILE_HEIGHT - 15);
}

void PlayerTexture::renderRight(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(head, x + 46, y + 15, 1);
    EntityTexture::render(shield, x + 40, y + 30, frame + 18);
    EntityTexture::render(body, x + 37, y + 30, frame + 18);
    EntityTexture::render(helmet, x + 45, y + 11, 1);
    EntityTexture::render(weapon, x + 37, y + 20, frame + 18);
    nickname.render(x + TILE_WIDTH/2 - textNicknameOffset, y + TILE_HEIGHT - 15);
    level.render(x + TILE_WIDTH/2 + textNicknameOffset - textLevelOffset, y + TILE_HEIGHT - 15);
}

void PlayerTexture::renderLeft(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(head, x + 43, y + 15, 2);
    EntityTexture::render(weapon, x + 33, y + 20, frame + 12);
    EntityTexture::render(body, x + 37, y + 30, frame + 12);
    EntityTexture::render(helmet, x + 43, y + 11, 2);
    EntityTexture::render(shield, x + 47, y + 30, frame + 12);
    nickname.render(x + TILE_WIDTH/2 - textNicknameOffset, y + TILE_HEIGHT - 15);
    level.render(x + TILE_WIDTH/2 + textNicknameOffset - textLevelOffset, y + TILE_HEIGHT - 15);
}

void PlayerTexture::setLevel(const std::string &_level) {
    *(level.updateText( " (" + _level + ")"));
    textLevelOffset = level.getTextTextureWidth();
    textNicknameOffset = (nickname.getTextTextureWidth() + textLevelOffset)/2;
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

