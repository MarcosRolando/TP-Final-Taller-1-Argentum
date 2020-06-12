//
// Created by marcos on 6/6/20.
//

#include "Texture.h"

Texture::Texture(SDL_Renderer& renderer, int xOff, int yOff) : renderer(renderer) {
    //Initialize
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
    xOffset = xOff;
    yOffset = yOff;
}

Texture::~Texture() {
    //Deallocate
    free();
}

void Texture::loadFromFile(const std::string& path, ColorKey_t key) {
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        throw SDLException("Unable to load image %s! SDL_image Error: %s\n",
                                                path.c_str(), IMG_GetError() );
    } else {
        //Color key image
        if (key.red > -1 && key.green > -1 && key.blue > -1) {
            SDL_SetColorKey(loadedSurface, SDL_TRUE,
                            SDL_MapRGB(loadedSurface->format, key.red, key.green, key.blue));
            /*Con esto aclaras que pixel hacer transparente*/
        }

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(&renderer, loadedSurface);
        if (newTexture == nullptr) {
            throw SDLException("Unable to create texture from %s! "
                               "SDL Error: %s\n", path.c_str(), SDL_GetError());
        } else {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
}

void Texture::free() {
    //Free texture if it exists
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::render(int x, int y, int spritePosition, int scale) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x + xOffset, y + yOffset, mWidth, mHeight};
    SDL_Rect& clip = gSpriteClips.at(spritePosition);

    //Set clip rendering dimensions
    renderQuad.w = clip.w*scale;
    renderQuad.h = clip.h*scale;

    //Render to screen
    SDL_RenderCopy(&renderer, mTexture, &clip, &renderQuad);
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
void Texture::loadFromRenderedText( std::string textureText, SDL_Color
textColor, TTF_Font* font ) {
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str
            (), textColor);
    if( textSurface == NULL ) {
        throw SDLException("Unable to render text surface! SDL_ttf Error:"
                           " %s\n", TTF_GetError());
    } else {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( &renderer, textSurface );
        if( mTexture == NULL ) {
            throw SDLException("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
}

void Texture::renderText(int x, int y) {
//Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Render to screen
    SDL_RenderCopy(&renderer, mTexture, NULL, &renderQuad);
}

