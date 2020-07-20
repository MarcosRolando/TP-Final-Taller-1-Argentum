//
// Created by marcos on 6/8/20.
//

#ifndef ARGENTUM_NPCTEXTURE_H
#define ARGENTUM_NPCTEXTURE_H

#include "EntityTexture.h"
#include "../../libs/TPException.h"
#include "TextureRepository.h"
#include "../Graphics/Text/Text.h"

/*Representa la textura de un npc*/

class NPCTexture : public EntityTexture {
private:
    TextureRepository& textureRepo;
    Font textFont;
    Texture* body;
    Text level;

public:
    explicit NPCTexture(TextureRepository& repo, TextureID texture, std::string&& _level = "");
    void renderFront(int x, int y, int frame) override;
    void renderBack(int x, int y, int frame) override;
    void renderRight(int x, int y, int frame) override;
    void renderLeft(int x, int y, int frame) override;
    void setLevel(std::string& _level);
};


#endif //ARGENTUM_NPCTEXTURE_H
