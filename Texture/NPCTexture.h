//
// Created by marcos on 6/8/20.
//

#ifndef ARGENTUM_NPCTEXTURE_H
#define ARGENTUM_NPCTEXTURE_H

#include "EntityTexture.h"
#include "../SDLException.h"

class NPCTexture : public EntityTexture {
private:
    Texture body;

public:
    NPCTexture(SDL_Renderer& renderer, std::string& image);

    explicit NPCTexture(SDL_Renderer& renderer) : body(renderer) {}

    void setImage(std::string& image);

    void renderFront(int x, int y, int frame) override;
    void renderBack(int x, int y, int frame) override;
    void renderRight(int x, int y, int frame) override;
    void renderLeft(int x, int y, int frame) override;

private:
    void _addSprites(int y, bool lateralSide);
};


#endif //ARGENTUM_NPCTEXTURE_H
