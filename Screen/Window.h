//
// Created by marcos on 11/6/20.
//

#ifndef ARGENTUM_WINDOW_H
#define ARGENTUM_WINDOW_H

#include <SDL.h>
#include <unordered_map>

enum Viewports {
    ScreenViewport,
    MapViewport,
    InventoryViewport,
    MinichatViewport,
    PlayerInfoViewport
};


class Window {
private:
    //Window data
    SDL_Window* mWindow;
    SDL_Renderer* renderer;

    std::unordered_map<Viewports, SDL_Rect> viewports;
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

    SDL_Renderer& getRenderer();

    //Handles window events
    void handleEvent(SDL_Event& e);

    bool isMinimized() const;

    void clear();

    void show();

    int getWidth() const;
    int getHeight() const;

    ~Window();

    void setViewport(Viewports viewport);

private:
    void _createViewports();
    //Creates window
    void _createWindow();
    //Creates renderer from internal window
    void _createRenderer();
    static void _initializeSDL();
};

#endif //ARGENTUM_WINDOW_H
