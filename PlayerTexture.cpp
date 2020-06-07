//
// Created by marcos on 6/6/20.
//

#include "PlayerTexture.h"
const int SCALE = 3; /*Factor de escala de la imagen*/

PlayerTexture::PlayerTexture(SDL_Renderer &renderer, std::string &helmetImage,
                             std::string &headImage, std::string &bodyImage,
                             std::string& weaponImage) : PlayerTexture(renderer) {

    setHelmetImage(helmetImage);
    setHeadImage(headImage);
    setBodyImage(bodyImage);
    setWeaponImage(weaponImage);
}


PlayerTexture::PlayerTexture(SDL_Renderer &renderer, std::string&& helmetImage,
                             std::string&& headImage, std::string&& bodyImage,
                             std::string&& weaponImage) :
                             PlayerTexture(renderer, helmetImage, headImage,
                                     bodyImage, weaponImage) {}

void PlayerTexture::setHelmetImage(std::string& helmetImage) {
    //todo
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

void PlayerTexture::setBodyImage(std::string& bodyImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        body.loadFromFile( bodyImage, key);
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

void PlayerTexture::renderFront(int x, int y, int bodyFrame) {
    if (bodyFrame < 0 || bodyFrame > 5) throw SDLException("I dont have that character frame!");
    _renderHead(x + 12, y - 26, 0);
    //_renderHelmet(x, y); todo
    _renderBody(x, y, bodyFrame);
    //_renderWeapon(); todo
}

void PlayerTexture::renderBack(int x, int y, int bodyFrame) {
    if (bodyFrame < 0 || bodyFrame > 5) throw SDLException("I dont have that character frame!");
    _renderHead(x + 12, y - 26, 3);
    //_renderHelmet(x, y); todo
    _renderBody(x, y, bodyFrame + 6);
    //_renderWeapon(); todo
}

void PlayerTexture::renderRight(int x, int y, int bodyFrame) {
    if (bodyFrame < 0 || bodyFrame > 5) throw SDLException("I dont have that character frame!");
    _renderHead(x + 13, y - 26, 1);
    //_renderHelmet(x, y); todo
    _renderBody(x, y, bodyFrame + 18);
    //_renderWeapon(); todo
}

void PlayerTexture::renderLeft(int x, int y, int bodyFrame) {
    if (bodyFrame < 0 || bodyFrame > 5) throw SDLException("I dont have that character frame!");
    _renderHead(x + 8, y - 26, 2);
    //_renderHelmet(x, y); todo
    _renderBody(x, y, bodyFrame + 12);
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

