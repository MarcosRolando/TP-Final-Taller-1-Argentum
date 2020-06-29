//
// Created by ivan on 26/6/20.
//

#include "ClientEventHandler.h"
#include "EventBlockingQueue.h"

void ClientEventHandler::run() {
    Selector& selector = game.getSelector();
    Minichat& minichat = game.getMinichat();
    Window& window = game.getWindow();

    while (!quit) {
        std::unique_ptr<SDL_Event> e = events.pop();
        if (e) { /*Si terminamos cerramos la cola entonces devuelve nullptr*/
            if (e->type == SDL_QUIT) {
                quit = true;
                break;
            }
            std::string a = " ";
            selector.handleEvent(*e, game.getPlayerInfo().getXPos(),
                                 game.getPlayerInfo().getYPos(), window);
            minichat.handleEvent(*e, game.getWindow());

            if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
                switch (e->key.keysym.sym) {
                    case SDLK_UP:
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_LEFT:
                        break;
                    case SDLK_RIGHT:
                        break;
                }

            }
        }
    }
}
