//
// Created by marcos on 6/6/20.
//

#include "Texture.h"

Texture::Texture(SDL_Renderer& renderer) : renderer(renderer) {
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
    xOffset = 0;
    yOffset = 0;
    defaultScale = 1;
}

Texture::~Texture() {
    _free();
}

void Texture::loadFromFile(const std::string& path, ColorKey_t key, int xOff, int yOff,
                                                                int scale) {
    //Libero la textura anterior
    _free();

    //cargo la imagen de path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        throw TPException("Unable to load image %s! SDL_image Error: %s\n",
                          path.c_str(), IMG_GetError() );
    } else {
        if (key.red > -1 && key.green > -1 && key.blue > -1) {
            SDL_SetColorKey(loadedSurface, SDL_TRUE,
                            SDL_MapRGB(loadedSurface->format, key.red, key.green, key.blue));
            /*Con esto aclaras que pixel hacer transparente*/
        }

        //Crea la textura
        mTexture = SDL_CreateTextureFromSurface(&renderer, loadedSurface);
        if (mTexture == nullptr) {
            //Si falla libero la superficie
            SDL_FreeSurface(loadedSurface);
            throw TPException("Unable to create texture from %s! "
                               "Graphics Error: %s\n", path.c_str(), SDL_GetError());
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Libero la superficie
        SDL_FreeSurface(loadedSurface);
    }

    xOffset = xOff;
    yOffset = yOff;
    defaultScale = scale;
}

void Texture::_free() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::render(int x, int y, int spritePosition, double angle, int scale) {
    SDL_Rect renderQuad = {x + xOffset, y + yOffset, mWidth, mHeight};
    SDL_Rect& clip = gSpriteClips.at(spritePosition);

    //Setea las dimensiones del rectangulo a renderizar
    renderQuad.w = clip.w*scale;
    renderQuad.h = clip.h*scale;

    //Renderiza
    SDL_RenderCopyEx(&renderer, mTexture, &clip, &renderQuad, angle, nullptr, SDL_FLIP_NONE);
}

void Texture::addSprite(int x, int y, int width, int height) {
    gSpriteClips.push_back({x, y, width, height});
}


Texture::Texture(Texture&& other) noexcept : renderer(other.renderer){
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    other.mWidth = 0;
    other.mHeight = 0;
    xOffset = other.xOffset;
    yOffset = other.yOffset;
    other.xOffset = 0;
    other.yOffset = 0;
    defaultScale = other.defaultScale;
    other.defaultScale = 1;
    mTexture = other.mTexture;
    other.mTexture = nullptr;
    gSpriteClips = std::move(other.gSpriteClips);
}

SpriteDimensions_t Texture::getSpriteDimensions(int spritePosition) {
    SDL_Rect& spriteDimensions = gSpriteClips[spritePosition];
    SpriteDimensions_t dimensions = {spriteDimensions.w, spriteDimensions.h};
    return dimensions;
}

/* Crea una textura con texto */
void Texture::loadFromRenderedText(const std::string& text, SDL_Color
                                                textColor, TTF_Font* font ) {
    //Libero la textura anterior
    _free();

    //Creo una superficie con el texto
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if( textSurface == nullptr ) {
        throw TPException("Unable to _render text surface! SDL_ttf Error:"
                           " %s\n", TTF_GetError());
    } else {
        //Crea la textura
        mTexture = SDL_CreateTextureFromSurface( &renderer, textSurface );

        if( mTexture == nullptr ) {
            //Si falla libera la superficie
            SDL_FreeSurface(textSurface);
            throw TPException("Unable to create texture from rendered text! Graphics Error: %s\n", SDL_GetError());
        } else {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Libero al superficie
        SDL_FreeSurface(textSurface);
    }
}

void Texture::renderText(int x, int y) {
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy(&renderer, mTexture, nullptr, &renderQuad);
}

void Texture::render(int x, int y, int spritePosition, double angle) {
    render(x, y, spritePosition, angle, defaultScale);
}
