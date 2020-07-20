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
    SDL_Renderer& renderer;
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
    int xOffset;
    int yOffset;
    int defaultScale;
    std::vector<SDL_Rect> gSpriteClips; /*Sprites de la textura*/

public:
    Texture(SDL_Renderer& renderer);
    ~Texture();
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&& other) noexcept;

    /*Carga la imagen de path, ignorando el color recibido en key. Opcionalmente
     * se le puede setear un offset de renderizacion y una escala distinta a la
     * imagen*/
    void loadFromFile(const std::string& path, ColorKey_t key = {-1, -1, -1},
                                    int xOff = 0, int yOff = 0, int scale = 1);

    /*Especifica una dimension (un clip) que representa un sprite de la textura*/
    void addSprite(int x, int y, int width, int height);

    /*Hago sobrecarga para poder pasar por parametro default a la escala de la textura
     * cuando la cree*/
    void render(int x, int y, int spritePosition = 0, double angle = 0);

    /*Renderiza el sprite de la textura en la posicion, angulo y escala indicados*/
    void render(int x, int y, int spritePosition, double angle, int scale);

    /*Retorna las dimensiones del sprite de la textura*/
    SpriteDimensions_t getSpriteDimensions(int spritePosition = 0);

    /*Crea una textura en base al texto recibido*/
    void loadFromRenderedText(const std::string& text, SDL_Color textColor, TTF_Font* font);


private:
    //Deallocates texture
    void _free();
};


#endif //ARGENTUM_TEXTURE_H
