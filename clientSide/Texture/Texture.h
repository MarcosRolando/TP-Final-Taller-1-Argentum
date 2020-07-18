//
// Created by marcos on 6/6/20.
//

#ifndef ARGENTUM_TEXTURE_H
#define ARGENTUM_TEXTURE_H

/*Esta clase representa la textura cargada. La textura puede contener mas de
 * una imagen, permitiendo renderizar solo lo que el programador elija*/

#include <SDL.h>
#include <SDL_image.h>
#include "../../libs/TPException.h"
#include "../Graphics/Text/Font.h"
#include <string>
#include <vector>


struct ColorKey_t {
    int red;
    int green;
    int blue;
};

struct SpriteDimensions_t {
    int width;
    int height;
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
    int defaultScale;
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
                                    int xOff = 0, int yOff = 0, int scale = 1);

    /*Especifica una dimension (un clip) que representa un sprite de la textura*/
    void addSprite(int x, int y, int width, int height);

    /*Hago sobrecarga para poder pasar por parametro default a la escala de la textura
     * cuando la cree*/
    void render(int x, int y, int spritePosition = 0, double angle = 0);

    //Renders texture at given point
    void render(int x, int y, int spritePosition, double angle, int scale);

    SpriteDimensions_t getSpriteDimensions(int spritePosition = 0);

    void loadFromRenderedText(const std::string& text, SDL_Color
    textColor, TTF_Font* font );

    void renderText(int x, int y);

private:
    //Deallocates texture
    void _free();
};


#endif //ARGENTUM_TEXTURE_H
