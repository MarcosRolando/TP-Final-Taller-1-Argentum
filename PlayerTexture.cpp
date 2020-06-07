//
// Created by marcos on 6/6/20.
//

#include "PlayerTexture.h"

PlayerTexture::PlayerTexture(SDL_Renderer &renderer, std::string &helmetImage,
                             std::string &headImage, std::string &bodyImage,
                             std::string& weaponImage) : PlayerTexture(renderer) {

    setHelmetImage(helmetImage);
    setHeadImage(helmetImage);
    setBodyImage(helmetImage);
    setWeaponImage(helmetImage);
}

void PlayerTexture::setHelmetImage(std::string& helmetImage) {

}

void PlayerTexture::setHeadImage(std::string& headImage) {

}

void PlayerTexture::setBodyImage(std::string& bodyImage) {

}

void PlayerTexture::setWeaponImage(std::string& weaponImage) {

}
