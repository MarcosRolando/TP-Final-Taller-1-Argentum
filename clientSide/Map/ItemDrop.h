//
// Created by marcos on 6/13/20.
//

#ifndef ARGENTUM_ITEMDROP_H
#define ARGENTUM_ITEMDROP_H

#include "../Texture/Texture.h"
#include "Coordinate.h"

/*Esta clase representa la imagen particular de un item (el drop). Se renderiza
 * en el mapa cuando esta droppeado en un tile o tambien en el inventario*/

class ItemDrop {
private:
    SDL_Rect box{};
    Texture* sTexture;

public:
    ItemDrop(Coordinate position);

    /*Renderiza el item*/
    void render(SDL_Rect& camera);

    /*Setea la textura del item a renderizar*/
    void setItem(Texture* itemTexture);
};


#endif //ARGENTUM_ITEMDROP_H
