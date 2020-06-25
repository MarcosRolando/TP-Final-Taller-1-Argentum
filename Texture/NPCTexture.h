//
// Created by marcos on 6/8/20.
//

#ifndef ARGENTUM_NPCTEXTURE_H
#define ARGENTUM_NPCTEXTURE_H

#include "EntityTexture.h"
#include "../TPException.h"
#include "TextureRepository.h"

class NPCTexture : public EntityTexture {
private:
    TextureRepository& textureRepo;
    Texture* body;

public:
    explicit NPCTexture(TextureRepository& repo, ObjectID texture);

    void renderFront(int x, int y, int frame) override;
    void renderBack(int x, int y, int frame) override;
    void renderRight(int x, int y, int frame) override;
    void renderLeft(int x, int y, int frame) override;
};


#endif //ARGENTUM_NPCTEXTURE_H
