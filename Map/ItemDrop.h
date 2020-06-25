//
// Created by marcos on 6/13/20.
//

#ifndef ARGENTUM_ITEMDROP_H
#define ARGENTUM_ITEMDROP_H

#include "../Texture/Texture.h"

class ItemDrop {
private:
    //The attributes of the tile
    SDL_Rect box{};
    Texture* sTexture;

public:
    ItemDrop(int x, int y);

    void render(SDL_Rect& camera);

    void setItem(Texture& itemTexture);
};


#endif //ARGENTUM_ITEMDROP_H