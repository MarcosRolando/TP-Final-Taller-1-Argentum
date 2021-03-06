//
// Created by marcos on 6/9/20.
//

#ifndef ARGENTUM_ENTITYTEXTURE_H
#define ARGENTUM_ENTITYTEXTURE_H

#include "Texture.h"
#include "../Graphics/Text/Text.h"

/*Clase Abstracta, los hijos deben implementar la renderizacion*/

class EntityTexture {
public:
    virtual void renderFront(int x, int y, int frame) = 0;
    virtual void renderBack(int x, int y, int frame) = 0;
    virtual void renderRight(int x, int y, int frame) = 0;
    virtual void renderLeft(int x, int y, int frame) = 0;
    static void render(Texture* texture, int x, int y, int spritePosition);
    virtual ~EntityTexture() = default;
};


#endif //ARGENTUM_ENTITYTEXTURE_H
