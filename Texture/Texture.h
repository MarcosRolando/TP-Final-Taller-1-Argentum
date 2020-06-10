//
// Created by marcos on 6/6/20.
//

#ifndef ARGENTUM_TEXTURE_H
#define ARGENTUM_TEXTURE_H

/*Esta clase representa la textura cargada. La textura puede contener mas de
 * una imagen, permitiendo renderizar solo lo que el programador elija*/

#include <SDL.h>
#include <SDL_image.h>
#include "../SDLException.h"
#include <string>
#include <vector>


struct ColorKey_t {
    int red;
    int green;
    int blue;
};

class Texture {
private:
    SDL_Renderer& renderer; /*El renderer es uno solo asociado a la ventana (que tambien es una sola)*/
    //The actual hardware texture
    SDL_Texture* mTexture;
    //Image dimensions
    int mWidth;
    int mHeight;
    //Scene sprites
    std::vector<SDL_Rect> gSpriteClips;

public:
    //Initializes variables
    explicit Texture(SDL_Renderer& renderer);

    //Deallocates memory
    ~Texture();

    Texture(const Texture&) = delete;

    Texture(Texture&& other) noexcept;

    //Loads image at specified path
    void loadFromFile(const std::string& path, ColorKey_t key = {-1, -1, -1});

    /*Especifica una dimension (un clip) que representa un sprite de la textura*/
    void addSprite(int x, int y, int width, int height);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render( int x, int y, int spritePosition, int scale = 1);
};


#endif //ARGENTUM_TEXTURE_H
