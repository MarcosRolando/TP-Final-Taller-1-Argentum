//
// Created by marcos on 6/9/20.
//

#include "EntityTexture.h"

const int SCALE = 2; /*Factor de escala de la imagen*/

void EntityTexture::render(Texture& texture, int x, int y, int spritePosition) {
    if (texture.loadedTexture()) texture.render(x, y, spritePosition, SCALE);
}