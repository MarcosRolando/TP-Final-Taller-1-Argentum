//
// Created by marcos on 6/6/20.
//

#ifndef ARGENTUM_TEXTURE_H
#define ARGENTUM_TEXTURE_H

/*Esta clase representa la textura cargada. La textura puede contener mas de
 * una imagen, permitiendo renderizar solo lo que el programador elija*/

#include <SDL.h>
#include <SDL_image.h>
#include "SDLException.h"
#include <string>

class Texture {
private:
    SDL_Renderer& renderer; /*El renderer es uno solo asociado a la ventana (que tambien es una sola)*/
    //Image dimensions
    int mWidth;
    int mHeight;

public:
    //Initializes variables
    explicit Texture(SDL_Renderer& renderer);

    //Deallocates memory
    ~Texture();

    //Loads image at specified path
    void loadFromFile(const std::string& path);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = nullptr, int scale = 1);

    //Gets image dimensions
    int getWidth() const;
    int getHeight() const;

private:
    //The actual hardware texture
    SDL_Texture* mTexture;
};


#endif //ARGENTUM_TEXTURE_H
