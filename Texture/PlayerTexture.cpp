//
// Created by marcos on 6/6/20.
//

#include "PlayerTexture.h"

PlayerTexture::PlayerTexture(SDL_Renderer &renderer, EquipmentImages& images)
                                                : PlayerTexture(renderer) {

    if (!images.helmetImage.empty()) setHelmetImage(images.helmetImage);
    setHeadImage(images.headImage);
    setBodyImage(images.bodyImage);
    if (!images.shieldImage.empty()) setShieldImage(images.shieldImage);
    if (!images.weaponImage.empty()) setWeaponImage(images.weaponImage);
}

void PlayerTexture::setHelmetImage(std::string& helmetImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        helmet.loadFromFile(helmetImage, key);
        helmet.addSprite(0, 0, 17, 17);
        helmet.addSprite(17, 0, 17, 17);
        helmet.addSprite(34, 0, 17, 17);
        helmet.addSprite(51, 0, 17, 17);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void PlayerTexture::setHeadImage(std::string& headImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        head.loadFromFile(headImage, key);
        head.addSprite(0, 0, 17, 15);
        head.addSprite(17, 0, 17, 15);
        head.addSprite(34, 0, 17, 15);
        head.addSprite(51, 0, 17, 15);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void PlayerTexture::_addBodySprites(int y, bool lateralSide) {
    body.addSprite(0, y, 24, 45); /*hasta 24 porque sino en la plate armor hay un poco de la otra imagen*/
    body.addSprite(25, y, 25, 45);
    body.addSprite(51, y, 24, 45); /*pongo 51 porque sino se veia un poco del pie de otro en algunas ropas*/
    body.addSprite(75, y, 25, 45);
    body.addSprite(100, y, 25, 45);
    if (lateralSide) body.addSprite(100, y, 25, 45);
    else body.addSprite(125, y, 25, 45);
}

void PlayerTexture::_addShieldSprites(int y, bool lateralSide) {
    shield.addSprite(0, y, 25, 35);
    shield.addSprite(26, y, 25, 35);
    shield.addSprite(51, y, 24, 35);
    shield.addSprite(76, y, 25, 35);
    shield.addSprite(101, y, 24, 35);
    if (lateralSide) shield.addSprite(101, y, 24, 35);
    else shield.addSprite(126, y, 25, 35);
}

void PlayerTexture::_addWeaponSprites(int y, bool lateralSide) {
    weapon.addSprite(0, y, 24, 45);
    weapon.addSprite(25, y, 25, 45);
    weapon.addSprite(51, y - 1, 23, 45);
    weapon.addSprite(76, y - 1, 23, 45);
    weapon.addSprite(101, y - 1, 24, 45);
    if (lateralSide) weapon.addSprite(101, y, 24, 45);
    else weapon.addSprite(126, y, 25, 45);
}

void PlayerTexture::setBodyImage(std::string& bodyImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        body.loadFromFile(bodyImage, key);
        /*Front*/
        _addBodySprites(0, false);
        /*Back*/
        _addBodySprites(45, false);
        /*Left*/
        _addBodySprites(90, true);
        /*Rigth*/
        _addBodySprites(135, true);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void PlayerTexture::setShieldImage(std::string& shieldImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        shield.loadFromFile(shieldImage, key);
        /*Front*/
        _addShieldSprites(0, false);
        /*Back*/
        _addShieldSprites(45, false);
        /*Left*/
        _addShieldSprites(90, true);
        /*Rigth*/
        _addShieldSprites(135, true);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void PlayerTexture::setWeaponImage(std::string& weaponImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        weapon.loadFromFile(weaponImage, key);
        /*Front*/
        _addWeaponSprites(0, false);
        /*Back*/
        _addWeaponSprites(45, false);
        /*Left*/
        _addWeaponSprites(90, true);
        /*Rigth*/
        _addWeaponSprites(135, true);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void PlayerTexture::renderFront(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw SDLException("I dont have that character frame!");
    EntityTexture::render(head, x + 8, y - 15, 0);
    EntityTexture::render(body, x, y, frame);
    EntityTexture::render(helmet, x + 8, y - 19, 0);
    EntityTexture::render(shield, x + 15, y, frame);
    EntityTexture::render(weapon, x, y - 10, frame);
}

void PlayerTexture::renderBack(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw SDLException("I dont have that character frame!");
    EntityTexture::render(head, x + 8, y - 15, 3);
    EntityTexture::render(weapon, x + 5, y - 10, frame + 6);
    EntityTexture::render(shield, x, y - 15, frame + 6);
    EntityTexture::render(body, x, y, frame + 6);
    EntityTexture::render(helmet, x + 8, y - 19, 3);
}

void PlayerTexture::renderRight(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw SDLException("I dont have that character frame!");
    EntityTexture::render(head, x + 9, y - 15, 1);
    EntityTexture::render(shield, x + 3, y, frame + 18);
    EntityTexture::render(body, x, y, frame + 18);
    EntityTexture::render(helmet, x + 8, y - 19, 1);
    EntityTexture::render(weapon, x, y - 10, frame + 18);
}

void PlayerTexture::renderLeft(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw SDLException("I dont have that character frame!");
    EntityTexture::render(head, x + 6, y - 15, 2);
    EntityTexture::render(weapon, x - 4, y - 10, frame + 12);
    EntityTexture::render(body, x, y, frame + 12);
    EntityTexture::render(helmet, x + 6, y - 19, 2);
    EntityTexture::render(shield, x + 10, y, frame + 12);
}

