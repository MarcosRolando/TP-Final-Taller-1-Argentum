//
// Created by ivan on 26/6/20.
//

#include "ClientEventHandler.h"
#include "EventBlockingQueue.h"
#include <msgpack.hpp>

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
            selector.handleEvent(*e, game.getPlayerInfo().getXPos(),
                                 game.getPlayerInfo().getYPos(), window);
            minichat.handleEvent(*e, game.getWindow());

            if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
                _handleMoveKeys(*e);
            }
        }
        if (msgBuffer.rdbuf()->in_avail() != 0) { /*Nos cargaron un mensaje*/
            std::string aux = msgBuffer.str();
            uint32_t length = htonl(aux.size());
            std::vector<char> buffer
        }
    }
}

void ClientEventHandler::_handleMoveKeys(SDL_Event& e) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::MOVE);
    msgpack::type::tuple<GameType::Direction> direction;
    switch (e.key.keysym.sym) {
        case SDLK_UP:
            direction = {GameType::DIRECTION_UP};
            msgpack::pack(msgBuffer, event);
            msgpack::pack(msgBuffer, direction);
            break;
        case SDLK_DOWN:
            direction = {GameType::DIRECTION_DOWN};
            msgpack::pack(msgBuffer, event);
            msgpack::pack(msgBuffer, direction);
            break;
        case SDLK_LEFT:
            direction = {GameType::DIRECTION_LEFT};
            msgpack::pack(msgBuffer, event);
            msgpack::pack(msgBuffer, direction);
            break;
        case SDLK_RIGHT:
            direction = {GameType::DIRECTION_RIGHT};
            msgpack::pack(msgBuffer, event);
            msgpack::pack(msgBuffer, direction);
            break;
    }
}
