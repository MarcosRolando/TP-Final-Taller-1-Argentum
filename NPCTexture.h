//
// Created by marcos on 6/8/20.
//

#ifndef ARGENTUM_NPCTEXTURE_H
#define ARGENTUM_NPCTEXTURE_H

#include "Texture.h"
#include "SDLException.h"

class NPCTexture {
private:
    Texture body;

public:
    NPCTexture(SDL_Renderer& renderer, std::string& image);

    explicit NPCTexture(SDL_Renderer& renderer) : body(renderer) {}

    void setImage(std::string& image);

    void renderFront(int x, int y, int frame);
    void renderBack(int x, int y, int frame);
    void renderRight(int x, int y, int frame);
    void renderLeft(int x, int y, int frame);

private:
    void _addSprites(int y, bool lateralSide);
    void _render(int x, int y, int spritePosition);
};


#endif //ARGENTUM_NPCTEXTURE_H
