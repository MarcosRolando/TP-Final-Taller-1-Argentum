//
// Created by marcos on 6/6/20.
//

#ifndef ARGENTUM_PLAYERTEXTURE_H
#define ARGENTUM_PLAYERTEXTURE_H


#include "EntityTexture.h"
#include "../SDLException.h"
#include "TextureRepository.h"

struct EquipmentImages {
    TextureID helmet;
    TextureID head;
    TextureID body;
    TextureID shield;
    TextureID weapon;
};

class PlayerTexture : public EntityTexture {
private:
    TextureRepository& textureRepo;
    Texture* helmet;
    Texture* head;
    Texture* body;
    Texture* shield;
    Texture* weapon;

public:
    PlayerTexture(TextureRepository& repo, EquipmentImages equipment);

    void renderFront(int x, int y, int frame) override;
    void renderBack(int x, int y, int frame) override;
    void renderRight(int x, int y, int frame) override;
    void renderLeft(int x, int y, int frame) override;
};


#endif //ARGENTUM_PLAYERTEXTURE_H
