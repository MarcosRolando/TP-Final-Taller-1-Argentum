//
// Created by marcos on 6/6/20.
//

#ifndef ARGENTUM_TEXTURE_H
#define ARGENTUM_TEXTURE_H

/*Esta clase representa la textura cargada. La textura puede contener mas de
 * una imagen, permitiendo renderizar solo lo que el programador elija*/

#include <SDL.h>
#include <SDL_image.h>
#include "../SDL/SDLException.h"
#include "../SDL/Font.h"
#include <string>
#include <vector>


struct ColorKey_t {
    int red;
    int green;
    int blue;
};

struct SpriteDimensions_t {
    int witdth;
    int heigth;
};

class Texture {
private:
    SDL_Renderer& renderer; /*El renderer es uno solo asociado a la ventana (que tambien es una sola)*/
    //The actual hardware texture
    SDL_Texture* mTexture;
    //Image dimensions
    int mWidth;
    int mHeight;
    int xOffset;
    int yOffset;
    //Scene sprites
    std::vector<SDL_Rect> gSpriteClips;

public:
    //Initializes variables
    Texture(SDL_Renderer& renderer);

    //Deallocates memory
    ~Texture();

    Texture(const Texture&) = delete;

    Texture(Texture&& other) noexcept;

    //Loads image at specified path
    void loadFromFile(const std::string& path, ColorKey_t key = {-1, -1, -1},
                                                            int xOff = 0, int yOff = 0);

    /*Especifica una dimension (un clip) que representa un sprite de la textura*/
    void addSprite(int x, int y, int width, int height);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render( int x, int y, int spritePosition = 0, int scale = 1);

    SpriteDimensions_t getSpriteDimensions(int spritePosition);

    void loadFromRenderedText( std::string textureText, SDL_Color
    textColor, TTF_Font* font );

    void renderText(int x, int y);
};


#endif //ARGENTUM_TEXTURE_H
