//
// Created by marcos on 6/6/20.
//

#include "PlayerTexture.h"
const int SCALE = 3; /*Factor de escala de la imagen*/

PlayerTexture::PlayerTexture(SDL_Renderer &renderer, EquipmentImages& images)
                                                : PlayerTexture(renderer) {

    if (!images.helmetImage.empty()) setHelmetImage(images.helmetImage);
    setHeadImage(images.headImage);
    setBodyImage(images.bodyImage);
    if (!images.shieldImage.empty()) setShieldImage(images.shieldImage);
    setWeaponImage(images.weaponImage);
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
    shield.addSprite(5, y, 21, 35);
    shield.addSprite(30, y, 21, 35);
    shield.addSprite(55, y, 21, 35);
    shield.addSprite(80, y, 21, 35);
    shield.addSprite(105, y, 21, 35);
    if (lateralSide) shield.addSprite(105, y, 21, 35);
    else shield.addSprite(130, y, 21, 35);
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
    //todo
}

void PlayerTexture::renderFront(int x, int y, int bodyFrame) {
    if (bodyFrame < 0 || bodyFrame > 5) throw SDLException("I dont have that character frame!");
    _renderHead(x + 12, y - 26, 0);
    _renderBody(x, y, bodyFrame);
    _renderHelmet(x + 12, y - 30, 0);
    _renderShield(x + 25, y, bodyFrame);
    //_renderWeapon(); todo
}

void PlayerTexture::renderBack(int x, int y, int bodyFrame) {
    if (bodyFrame < 0 || bodyFrame > 5) throw SDLException("I dont have that character frame!");
    _renderHead(x + 12, y - 26, 3);
    _renderBody(x, y, bodyFrame + 6);
    _renderHelmet(x + 12, y - 30, 3);
    _renderShield(x, y, bodyFrame + 6);
    //_renderWeapon(); todo
}

void PlayerTexture::renderRight(int x, int y, int bodyFrame) {
    if (bodyFrame < 0 || bodyFrame > 5) throw SDLException("I dont have that character frame!");
    _renderHead(x + 13, y - 26, 1);
    _renderBody(x, y, bodyFrame + 18);
    _renderHelmet(x + 13, y - 30, 1);
    _renderShield(x + 12, y, bodyFrame + 18);
    //_renderWeapon(); todo
}

void PlayerTexture::renderLeft(int x, int y, int bodyFrame) {
    if (bodyFrame < 0 || bodyFrame > 5) throw SDLException("I dont have that character frame!");
    _renderHead(x + 8, y - 26, 2);
    _renderBody(x, y, bodyFrame + 12);
    _renderHelmet(x + 7, y - 30, 2);
    _renderShield(x + 10, y, bodyFrame + 12);
    //_renderWeapon(); todo
}

void PlayerTexture::_renderHead(int x, int y, int spritePosition) {
    head.render(x, y, spritePosition, SCALE);
}

void PlayerTexture::_renderHelmet(int x, int y, int spritePosition) {
    if (helmet.loadedTexture()) helmet.render(x, y, spritePosition, SCALE);
}

void PlayerTexture::_renderBody(int x, int y, int spritePosition) {
    body.render(x, y, spritePosition, SCALE);
}
void PlayerTexture::_renderShield(int x, int y, int spritePosition) {
    if (shield.loadedTexture()) shield.render(x, y, spritePosition, SCALE);
}

void PlayerTexture::_renderWeapon(int x, int y) {

}

