//
// Created by marcos on 10/6/20.
//

#ifndef ARGENTUM_STRUCTURE_H
#define ARGENTUM_STRUCTURE_H

#include "../Texture/Texture.h"
#include "Coordinate.h"

class Structure {
private:
    //The attributes of the tile
    SDL_Rect box{};
    Texture* sTexture;

public:
    Structure(Coordinate position, Texture* sTexture = nullptr);

    void setTexture(Texture& texture);

    void render(SDL_Rect& camera);

    //Get the collision box
    SDL_Rect getBox() const;

private:
    static bool _checkCollision(SDL_Rect a, SDL_Rect b);
};


#endif //ARGENTUM_STRUCTURE_H
