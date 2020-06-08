//
// Created by marcos on 6/8/20.
//

#include "NPCTexture.h"
const int SCALE = 3; /*Factor de escala de la imagen*/

NPCTexture::NPCTexture(SDL_Renderer &renderer, std::string &image) :
                                                        NPCTexture(renderer){
    setImage(image);
}

void NPCTexture::_addSprites(int y, bool lateralSide) {
    body.addSprite(0, y, 24, 52);
    body.addSprite(25, y, 25, 52);
    body.addSprite(51, y, 24, 52);
    body.addSprite(75, y, 25, 52);
    body.addSprite(100, y, 25, 52);
    if (lateralSide) body.addSprite(100, y, 25, 52);
    else body.addSprite(125, y, 25, 52);
}

void NPCTexture::setImage(std::string& image) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        body.loadFromFile(image, key);
        /*Front*/
        _addSprites(0, false);
        /*Back*/
        _addSprites(52, false);
        /*Left*/
        _addSprites(104, true);
        /*Rigth*/
        _addSprites(156, true);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void NPCTexture::renderFront(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw SDLException("I dont have that character frame!");
    _render(x, y - 30, frame);
}

void NPCTexture::renderBack(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw SDLException("I dont have that character frame!");
    _render(x, y - 30, frame + 6);
}

void NPCTexture::renderRight(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw SDLException("I dont have that character frame!");
    _render(x, y - 30, frame + 18);
}

void NPCTexture::renderLeft(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw SDLException("I dont have that character frame!");
    _render(x, y - 30, frame + 12);
}

void NPCTexture::_render(int x, int y, int spritePosition) {
    body.render(x, y, spritePosition, SCALE);
}