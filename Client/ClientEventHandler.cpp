//
// Created by ivan on 26/6/20.
//

#include "ClientEventHandler.h"
#include "BlockingQueue.hpp"
#include <msgpack.hpp>
#include "Socket.h"

MSGPACK_ADD_ENUM(GameType::Direction)
MSGPACK_ADD_ENUM(GameType::PlayerEvent)

void ClientEventHandler::run() {
    //Selector& selector = game.getSelector();
    Minichat& minichat = game.getMinichat();
   // Window& window = game.getWindow();

    try {
        while (!quit) {
            std::unique_ptr<SDL_Event> e = events.pop();
            if (e) { /*Si terminamos cerramos la cola entonces devuelve nullptr*/
                /*if (e->type == SDL_QUIT) {
                    quit = true;
                    break;
                }
                minichat.handleEvent(*e, game.getWindow());

                if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
                    _handleMoveKeys(*e);
                } else if (e->type == SDL_MOUSEBUTTONDOWN){
                    selector.handleEvent(*e, game.getPlayerInfo().getXPos(),
                                         game.getPlayerInfo().getYPos(), window);
                }*/
                switch (e->type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        if (e->key.repeat == 0) {//Ver si le agregamos para q pueda
                                                //mantener otras teclas
                            _handleMoveKeys(*e);
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        _handleMouseButtonDown(*e);
                        break;
                    case SDL_TEXTINPUT:
                        minichat.handleTextInput(*e);
                        break;
                    case SDL_MOUSEWHEEL:
                        minichat.handleMouseWheel(*e);
                        break;
                }
            }
            if (msgBuffer.rdbuf()->in_avail() != 0) { /*Nos cargaron un mensaje*/
                _sendMessage();
            }
        }
    } catch (...) {
        //do nothing
    }
}

void ClientEventHandler::_handleMouseButtonDown(SDL_Event& e){
    game.getMinichat().handleMouseButtonDown(game.getWindow());
    //game.getSelector().handleMouseButtonDown(e);
}

//Cambiarle el nombre a handleKeyDown
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
        case SDLK_BACKSPACE:
            game.getMinichat().handleBackspace();
            break;
        case SDLK_RETURN:
            game.getMinichat().handleReturnKey(); //Ver aca como manejar lo de mandar el msj parseado
            break;
    }
}
void ClientEventHandler::_loadBytes(std::vector<char>& buffer, void* data, unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        buffer[i] = *(reinterpret_cast<char *>(data) + i);
    }
}

void ClientEventHandler::_sendMessage() {
    std::string aux = msgBuffer.str();
    uint32_t length = htonl(aux.size());
    std::vector<char> buffer(sizeof(uint32_t));
    _loadBytes(buffer, &length, sizeof(uint32_t));
    std::copy(aux.begin(), aux.end(), std::back_inserter(buffer));
    socket.send(buffer.data(), buffer.size());
    msgBuffer.str(""); /*Reseteo el stringstream*/
    msgBuffer.clear();
}

