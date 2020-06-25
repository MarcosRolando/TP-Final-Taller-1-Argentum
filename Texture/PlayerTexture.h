//
// Created by marcos on 6/6/20.
//

#ifndef ARGENTUM_PLAYERTEXTURE_H
#define ARGENTUM_PLAYERTEXTURE_H


#include "EntityTexture.h"
#include "../TPException.h"
#include "TextureRepository.h"

struct PlayerEquipment {
    ObjectID helmet;
    ObjectID head;
    ObjectID body;
    ObjectID shield;
    ObjectID weapon;
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
    PlayerTexture(TextureRepository& repo, PlayerEquipment equipment);

    void renderFront(int x, int y, int frame) override;
    void renderBack(int x, int y, int frame) override;
    void renderRight(int x, int y, int frame) override;
    void renderLeft(int x, int y, int frame) override;
};


#endif //ARGENTUM_PLAYERTEXTURE_H
