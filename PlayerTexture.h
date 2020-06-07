//
// Created by marcos on 6/6/20.
//

#ifndef ARGENTUM_PLAYERTEXTURE_H
#define ARGENTUM_PLAYERTEXTURE_H

#include "Texture.h"
#include "SDLException.h"

class PlayerTexture {
private:
    Texture helmet;
    Texture head;
    Texture body;
    Texture weapon;

public:
    PlayerTexture(SDL_Renderer& renderer, std::string& helmetImage, std::string& headImage,
                std::string& bodyImage, std::string& weaponImage);
    explicit PlayerTexture(SDL_Renderer& renderer) : helmet(renderer), head(renderer),
                    body(renderer), weapon(renderer) {};
    void setHelmetImage(std::string& helmetImage);
    void setHeadImage(std::string& headImage);
    void setBodyImage(std::string& bodyImage);
    void setWeaponImage(std::string& weaponImage);
};


#endif //ARGENTUM_PLAYERTEXTURE_H
