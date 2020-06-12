//
// Created by marcos on 11/6/20.
//

#ifndef ARGENTUM_WINDOW_H
#define ARGENTUM_WINDOW_H

#include <SDL.h>

class Window {
private:
    //Window data
    SDL_Window* mWindow;
    SDL_Renderer* renderer;

    //Window dimensions
    int mWidth;
    int mHeight;

    //Window focus
    bool mMouseFocus;
    bool mKeyboardFocus;
    bool mFullScreen;
    bool mMinimized;

public:
    //Intializes internals
    Window();

    //Creates window
    void _createWindow();

    //Creates renderer from internal window
    void _createRenderer();

    SDL_Renderer& getRenderer();

    //Handles window events
    void handleEvent( SDL_Event& e );

    //Deallocates internals
    void free();

    ~Window();
};

#endif //ARGENTUM_WINDOW_H
