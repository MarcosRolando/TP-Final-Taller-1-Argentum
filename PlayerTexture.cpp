//
// Created by marcos on 6/6/20.
//

#include "PlayerTexture.h"
const int SCALE = 3; /*Factor de escala de la imagen*/

PlayerTexture::PlayerTexture(SDL_Renderer &renderer, std::string &helmetImage,
                             std::string &headImage, std::string &bodyImage,
                             std::string& weaponImage) : PlayerTexture(renderer) {

    setHelmetImage(helmetImage);
    setHeadImage(helmetImage);
    setBodyImage(helmetImage);
    setWeaponImage(helmetImage);
}


PlayerTexture::PlayerTexture(SDL_Renderer &renderer, std::string&& helmetImage,
                             std::string&& headImage, std::string&& bodyImage,
                             std::string&& weaponImage) : PlayerTexture(renderer) {

    setHelmetImage(helmetImage);
    setHeadImage(helmetImage);
    setBodyImage(helmetImage);
    setWeaponImage(helmetImage);
}

void PlayerTexture::setHelmetImage(std::string& helmetImage) {
    //todo
}

void PlayerTexture::setHeadImage(std::string& headImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        head.loadFromFile( headImage, key);
        head.addSprite(0, 0, 17, 15);
        head.addSprite(17, 0, 17, 15);
        head.addSprite(34, 0, 17, 15);
        head.addSprite(51, 0, 17, 15);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void PlayerTexture::_addBodySprites(int y) {
    body.addSprite(0, y, 25, 45);
    body.addSprite(25, y, 25, 45);
    body.addSprite(50, y, 25, 45);
    body.addSprite(75, y, 25, 45);
    body.addSprite(100, y, 25, 45);
    body.addSprite(125, y, 25, 45);
}

void PlayerTexture::setBodyImage(std::string& bodyImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        body.loadFromFile( bodyImage, key);
        /*Front*/
        _addBodySprites(0);
        /*Back*/
        _addBodySprites(45);
        /*Left*/
        _addBodySprites(90);
        /*Rigth*/
        _addBodySprites(135);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void PlayerTexture::setWeaponImage(std::string& weaponImage) {
    //todo
}

void PlayerTexture::setHelmetImage(std::string&& helmetImage) {
    setHelmetImage(helmetImage);
}

void PlayerTexture::setHeadImage(std::string&& headImage) {
    setHeadImage(headImage);
}

void PlayerTexture::setBodyImage(std::string&& bodyImage) {
    setBodyImage(bodyImage);
}

void PlayerTexture::setWeaponImage(std::string&& weaponImage) {
    setWeaponImage(weaponImage);
}

void PlayerTexture::renderStaticFront(int x, int y) {
    _renderHead(x + 12, y - 26, 0);
    //_renderHelmet(x, y); todo
    _renderBody(x, y, 0);
    //_renderWeapon(); todo
}

void PlayerTexture::renderStaticBack(int x, int y) {
    _renderHead(x + 12, y - 26, 3);
    //_renderHelmet(x, y); todo
    _renderBody(x, y, 6);
    //_renderWeapon(); todo
}

void PlayerTexture::renderStaticRight(int x, int y) {
    _renderHead(x + 13, y - 26, 1);
    //_renderHelmet(x, y); todo
    _renderBody(x, y, 18);
    //_renderWeapon(); todo
}

void PlayerTexture::renderStaticLeft(int x, int y) {
    _renderHead(x + 8, y - 26, 2);
    //_renderHelmet(x, y); todo
    _renderBody(x, y, 12);
    //_renderWeapon(); todo
}

void PlayerTexture::_renderHead(int x, int y, int spritePosition) {
    head.render( x, y, spritePosition, SCALE);
}

void PlayerTexture::_renderHelmet(int x, int y) {

}

void PlayerTexture::_renderBody(int x, int y, int spritePosition) {
    body.render(x, y, spritePosition, SCALE);
}

void PlayerTexture::_renderWeapon(int x, int y) {

}

