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
            if (e) {
                switch (e->type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        _handleMoveKeys(*e);
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
    int clickX, clickY;
    SDL_GetMouseState(&clickX, &clickY);
    //Escalo la posicion de click
    clickX = (float)clickX * ((float)DEFAULT_SCREEN_WIDTH/(float)game.getWindow().getWidth());
    clickY = (float)clickY * ((float)DEFAULT_SCREEN_HEIGHT/(float)game.getWindow().getHeight());

    game.getMinichat().handleMouseButtonDown({clickY, clickX}, game.getWindow());

    game.getSelector().handleEvent({clickY, clickX},
            {game.getPlayerInfo().getYPos(),game.getPlayerInfo().getXPos()},
            game.getWindow());

    if (e.button.button == SDL_BUTTON_RIGHT) {
        if (game.getSelector().isThereSelectedTile()){
            _processAttack(game.getSelector().getSelectedTile());
        } else if (game.getSelector().isThereSelectedInventorySlot()){
            //_processUnequipItem();
        }
    }


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
            //todo manejar el parseo del mensaje
            game.getMinichat().handleReturnKey();
            break;
    }
}

void ClientEventHandler::_processAttack(Coordinate selectedTile) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_ATTACK);
    msgpack::type::tuple<int32_t, int32_t> targetPosition;
    targetPosition = {selectedTile.i, selectedTile.j};
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, targetPosition);
}

//Esta y sendMessage hay que meterlas en una clase de protocol gral o algo asi
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

