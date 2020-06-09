//
// Created by marcos on 6/6/20.
//

#ifndef ARGENTUM_PLAYERTEXTURE_H
#define ARGENTUM_PLAYERTEXTURE_H

#include "Texture.h"
#include "../SDLException.h"

struct EquipmentImages {
    std::string helmetImage;
    std::string headImage;
    std::string bodyImage;
    std::string shieldImage;
    std::string weaponImage;
};

class PlayerTexture {
private:
    Texture helmet;
    Texture head;
    Texture body;
    Texture shield;
    Texture weapon;

public:
    PlayerTexture(SDL_Renderer& renderer, EquipmentImages& images);

    explicit PlayerTexture(SDL_Renderer& renderer) : helmet(renderer), head(renderer),
                    body(renderer), shield(renderer), weapon(renderer) {};

    void setHelmetImage(std::string& helmetImage);
    void setHeadImage(std::string& headImage);
    void setBodyImage(std::string& bodyImage);
    void setShieldImage(std::string& shieldImage);
    void setWeaponImage(std::string& weaponImage);

    void renderFront(int x, int y, int frame);
    void renderBack(int x, int y, int frame);
    void renderRight(int x, int y, int frame);
    void renderLeft(int x, int y, int frame);

private:
    void _addBodySprites(int y, bool lateralSide);
    void _addShieldSprites(int y, bool lateralSide);
    void _addWeaponSprites(int y, bool lateralSide);
    void _renderHead(int x, int y, int spritePosition);
    void _renderHelmet(int x, int y, int spritePosition);
    void _renderBody(int x, int y, int spritePosition);
    void _renderShield(int x, int y, int spritePosition);
    void _renderWeapon(int x, int y, int spritePosition);
};


#endif //ARGENTUM_PLAYERTEXTURE_H
