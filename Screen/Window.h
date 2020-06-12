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
    bool mMouseFocus; /*Por ahora no los uso*/
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
    void handleEvent(SDL_Event& e);

    bool isMinimized() const;

    void clear();

    void show();

    ~Window();
};

#endif //ARGENTUM_WINDOW_H
