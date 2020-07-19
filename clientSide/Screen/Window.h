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

/*Esta clase maneja la instancia de la ventana del juego, tiene el ownership
 * del renderizador y se encarga de mostrar los cambios renderizados y
 * setear los viewports*/

class Window {
private:
    SDL_Window* mWindow;
    SDL_Renderer* renderer;

    std::unordered_map<Viewports, SDL_Rect> viewports;
    int mWidth;
    int mHeight;

    bool mFullScreen;
    bool mMinimized;

public:
    Window();

    /* Maneja los eventos de la ventana. Por ejemplo resize o minimizar */
    bool handleEvent(SDL_Event& e);

    /* Limpia la ventana para poder renderizar */
    void clear();

    /* Muestra lo que haya renderizado */
    void show();

    /* Setea un viewport */
    void setViewport(Viewports viewport);

    SDL_Renderer& getRenderer();
    int getWidth() const;
    int getHeight() const;

    ~Window();

private:
    void _createViewports();
    void _createWindow();
    void _createRenderer();
    void _handleResizeEvent(SDL_Event& e, bool& handled);
};

#endif //ARGENTUM_WINDOW_H
