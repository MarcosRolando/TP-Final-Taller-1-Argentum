//
// Created by marcos on 6/6/20.
//

#include "Texture.h"

Texture::Texture(SDL_Renderer& renderer) : renderer(renderer) {
    //Initialize
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

Texture::~Texture() {
    //Deallocate
    free();
}

void Texture::loadFromFile(const std::string& path) {
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = nullptr;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        throw SDLException("Unable to load image %s! SDL_image Error: %s\n",
                                                path.c_str(), IMG_GetError() );
    } else {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE,
                        SDL_MapRGB(loadedSurface->format, 0, 0, 0));
                                /*Con esto aclaras que pixel hacer transparente*/

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(&renderer, loadedSurface);
        if (newTexture == nullptr) {
            throw SDLException("Unable to create texture from %s! "
                               "SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else {
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

void Texture::render(int x, int y, SDL_Rect* clip, int scale) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    //Set clip rendering dimensions
    if (clip != nullptr) {
        renderQuad.w = clip->w*scale;
        renderQuad.h = clip->h*scale;
    }

    //Render to screen
    SDL_RenderCopy(&renderer, mTexture, clip, &renderQuad);
}

int Texture::getWidth() const {
    return mWidth;
}

int Texture::getHeight() const {
    return mHeight;
}
