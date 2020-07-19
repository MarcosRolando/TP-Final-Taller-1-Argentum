//
// Created by marcos on 10/6/20.
//

#ifndef ARGENTUM_STRUCTURE_H
#define ARGENTUM_STRUCTURE_H

#include "../Texture/Texture.h"
#include "Coordinate.h"

/*Esta clase representa una estructura en el juego, esto puede variar
 * desde casas hasta arboles/arbustos o cadaveres*/

class Structure {
private:
    SDL_Rect box{};
    Texture* sTexture;

public:
    Structure(Coordinate position, Texture* sTexture = nullptr);

    /*Setea la textura a renderizar de la estructura*/
    void setTexture(Texture& texture);

    /*Renderiza la estructura si es visible en la camara del player*/
    void render(SDL_Rect& camera);

private:
    static bool _checkCollision(SDL_Rect a, SDL_Rect b);
};


#endif //ARGENTUM_STRUCTURE_H
