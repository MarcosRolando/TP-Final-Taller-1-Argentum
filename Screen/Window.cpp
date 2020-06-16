//
// Created by marcos on 11/6/20.
//

#include "Window.h"
#include "../GameConstants.h"
#include "../SDL/TPException.h"

Window::Window() {
    //Initialize non-existant window
    mWindow = nullptr;
    renderer = nullptr;
    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullScreen = false;
    mMinimized = false;
    mWidth = 0;
    mHeight = 0;
    _createWindow();
    _createRenderer();
    _createViewports();
}

void Window::_createViewports(){
    viewports.emplace(ScreenViewport, SDL_Rect{0,0,DEFAULT_SCREEN_WIDTH,
                                            DEFAULT_SCREEN_HEIGHT});
    viewports.emplace(MapViewport, SDL_Rect{20,236,DEFAULT_MAP_WIDTH,
                                             DEFAULT_MAP_HEIGHT});

    viewports.emplace(InventoryViewport, SDL_Rect{20 + DEFAULT_MAP_WIDTH,0,
                                                  DEFAULT_INVENTORY_WIDTH,
                                                  DEFAULT_INVENTORY_HEIGHT});

    viewports.emplace(MinichatViewport, SDL_Rect{0, DEFAULT_MAP_HEIGHT,
                                                 DEFAULT_MINICHAT_WIDTH,
                                            DEFAULT_MINICHAT_HEIGHT});

    viewports.emplace(PlayerInfoViewport, SDL_Rect{0, DEFAULT_MINICHAT_HEIGHT
    + DEFAULT_MAP_HEIGHT - 45, DEFAULT_MAP_WIDTH, 40});
}

void Window::_createWindow() {
    //Create window
    mWindow = SDL_CreateWindow( "Argentum Online", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if (mWindow != nullptr) {
        mMouseFocus = true;
        mKeyboardFocus = true;
        mWidth = DEFAULT_SCREEN_WIDTH;
        mHeight = DEFAULT_SCREEN_HEIGHT;
    } else {
        throw TPException("Window could not be created! SDL Error: %s\n", SDL_GetError());
    }
}

void Window::_createRenderer() {
    renderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) throw TPException("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Window::handleEvent(SDL_Event& e) {
    //Window event occured
    if (e.type == SDL_WINDOWEVENT) {
        switch (e.window.event) {
            //Get new dimensions and repaint on window size change
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                mWidth = e.window.data1;
                mHeight = e.window.data2;
                show();
                break;

                //Repaint on exposure
            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent(renderer);
                break;

                //Mouse entered window
            case SDL_WINDOWEVENT_ENTER:
                mMouseFocus = true;
                break;

                //Mouse left window
            case SDL_WINDOWEVENT_LEAVE:
                mMouseFocus = false;
                break;

                //Window has keyboard focus
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                mKeyboardFocus = true;
                mMinimized = false;
                break;

                //Window lost keyboard focus
            case SDL_WINDOWEVENT_FOCUS_LOST:
                mKeyboardFocus = false;
                break;

                //Window minimized
            case SDL_WINDOWEVENT_MINIMIZED:
                mMinimized = true;
                break;

                //Window maxized
            case SDL_WINDOWEVENT_MAXIMIZED:
                mMinimized = false;
                break;

                //Window restored
            case SDL_WINDOWEVENT_RESTORED:
                mMinimized = false;
                break;
        }
    }
        //Enter exit full screen on return key
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
        mWidth = DEFAULT_SCREEN_WIDTH;
        mHeight = DEFAULT_SCREEN_HEIGHT;
        if (mFullScreen) {
            SDL_SetWindowFullscreen(mWindow, SDL_FALSE);
            SDL_SetWindowSize(mWindow, mWidth, mHeight);
            mFullScreen = false;
        } else {
            //SDL_SetWindowSize(mWindow, mWidth, mHeight);
            SDL_SetWindowFullscreen(mWindow, SDL_TRUE);
            mFullScreen = true;
            mMinimized = false;
        }
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F2) {
        SDL_SetWindowFullscreen(mWindow, SDL_FALSE);
        mFullScreen = false;
        mWidth = DEFAULT_SCREEN_WIDTH;
        mHeight = DEFAULT_SCREEN_HEIGHT;
        SDL_RestoreWindow(mWindow);
        SDL_SetWindowSize(mWindow, mWidth, mHeight);
    }
}

SDL_Renderer& Window::getRenderer() {
    return *renderer;
}

Window::~Window() {
    if (renderer != nullptr) SDL_DestroyRenderer(renderer);
    if (mWindow != nullptr) SDL_DestroyWindow(mWindow);
    mMouseFocus = false;
    mKeyboardFocus = false;
    mWidth = 0;
    mHeight = 0;
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
}

void Window::show() {
    //Update screen
    float x_scale = (float)mWidth/(float)DEFAULT_SCREEN_WIDTH;
    float y_scale = (float)mHeight/(float)DEFAULT_SCREEN_HEIGHT;
    SDL_RenderSetScale(renderer, x_scale, y_scale);
    SDL_RenderPresent(renderer);
}

bool Window::isMinimized() const {
    return mMinimized;
}

void Window::setViewport(Viewports viewport){
    SDL_RenderSetViewport(renderer, &viewports.at(viewport));
}