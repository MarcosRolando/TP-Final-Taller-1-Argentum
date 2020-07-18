//
// Created by ivan on 26/6/20.
//

#include "ClientEventHandler.h"
#include "BlockingQueue.hpp"
#include <msgpack.hpp>
#include "../../libs/Socket.h"
#include "ClientProtocol.h"
#include "InputCommands/InputCommand.h"

MSGPACK_ADD_ENUM(GameType::Direction)
MSGPACK_ADD_ENUM(GameType::PlayerEvent)

/* Procesa los eventos del usuario y manda dicho evento con su informacion correspondiente al server */
void ClientEventHandler::run() {
    Minichat& minichat = game.getMinichat();

    try {
        while (!quit) {
            std::unique_ptr<SDL_Event> e = events.pop();
            if (e) {
                switch (e->type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        _handleKeyDown(*e);
                        break;
                    case SDL_KEYUP:
                        _handleKeyUp(*e);
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
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

/* Porcesa el evento de cuando se deja de apretar una tecla */
void ClientEventHandler::_handleKeyUp(SDL_Event& e) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_STOP_MOVING);
    switch (e.key.keysym.sym) {
        case SDLK_UP:
            msgpack::pack(msgBuffer, event);
            break;
        case SDLK_DOWN:
            msgpack::pack(msgBuffer, event);
            break;
        case SDLK_LEFT:
            msgpack::pack(msgBuffer, event);
            break;
        case SDLK_RIGHT:
            msgpack::pack(msgBuffer, event);
            break;
    }
}

/* Procesa el evento de cuando se hace click */
void ClientEventHandler::_handleMouseButtonDown(SDL_Event& e){
    int clickX, clickY;
    SDL_GetMouseState(&clickX, &clickY);
    //Escalo la posicion de click
    clickX = (float)clickX * ((float)DEFAULT_SCREEN_WIDTH/(float)game.getWindow().getWidth());
    clickY = (float)clickY * ((float)DEFAULT_SCREEN_HEIGHT/(float)game.getWindow().getHeight());

    game.getMinichat().handleMouseButtonDown({clickY, clickX}, game.getWindow());

    game.getSelector().handleEvent({clickY, clickX},{game.getPlayerInfo().getYPos(),
                         game.getPlayerInfo().getXPos()},game.getWindow());

    if (e.button.button == SDL_BUTTON_RIGHT) {
        if (Selector::hasSelectedTile({clickY, clickX})) {
            _processAttack(game.getSelector().getSelectedTile());
        }
        if (Selector::hasSelectedSlot({clickY, clickX})) {
            _processUseItem(game.getSelector().getInventorySlot());
        }
        if (Selector::hasSelectedEquipment({clickY, clickX})) {
            _processUnequipItem(game.getSelector().getSelectedEquipment());
        }
    }
}

/* Procesa el evento de cuando se apreta una tecla */
void ClientEventHandler::_handleKeyDown(SDL_Event& e) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_START_MOVING);
    msgpack::type::tuple<GameType::Direction> direction;
    if (e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                game.getSelector().resetTileSelection();
                direction = {GameType::DIRECTION_UP};
                msgpack::pack(msgBuffer, event);
                msgpack::pack(msgBuffer, direction);
                break;
            case SDLK_DOWN:
                game.getSelector().resetTileSelection();
                direction = {GameType::DIRECTION_DOWN};
                msgpack::pack(msgBuffer, event);
                msgpack::pack(msgBuffer, direction);
                break;
            case SDLK_LEFT:
                game.getSelector().resetTileSelection();
                direction = {GameType::DIRECTION_LEFT};
                msgpack::pack(msgBuffer, event);
                msgpack::pack(msgBuffer, direction);
                break;
            case SDLK_RIGHT:
                game.getSelector().resetTileSelection();
                direction = {GameType::DIRECTION_RIGHT};
                msgpack::pack(msgBuffer, event);
                msgpack::pack(msgBuffer, direction);
                break;
            case SDLK_BACKSPACE:
                game.getMinichat().handleBackspace();
                break;
            case SDLK_RETURN:
                _processCommandInput();
                break;
            case SDLK_TAB:
                if (SoundPlayer::isMusicPlaying()) {
                    game.getSoundPlayer().pauseMusic();
                } else {
                    game.getSoundPlayer().playMusic();
                }
                break;
        }
    }
}

/* Procesa el evento cuando apreto enter para ejecutar un comando del minichat */
void ClientEventHandler::_processCommandInput() {
    std::string cmd = game.getMinichat().handleReturnKey();
    if (cmd != ""){ //Si apreto enter y no hay texto handleReturnKey me devuelve esto
        if (cmd == "/clear") {
            game.getMinichat().clearMinichat();
        } else {
            std::unique_ptr<InputCommand> inputCmd;
            inputCmd = cmdVerifier.verifyCommand(game, std::move(cmd));
            if (inputCmd) {
                (*inputCmd)(msgBuffer);//Arma el mensaje y lo packea en msgBuffer
            } else {
                game.getMinichat().receiveText("Invalid command");
            }
        }
    }
}

/* Arma el buffer y lo envia para el evento de desequipar un item */
void ClientEventHandler::_processUnequipItem(GameType::EquipmentPlace _equipment){
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_UNEQUIP);
    msgpack::type::tuple<int32_t> equipment;
    equipment = _equipment;
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, equipment);
}

/* Arma el buffer y lo envia para el evento de equiparse un item */
void ClientEventHandler::_processUseItem(int _inventorySlot) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_USE_ITEM);
    msgpack::type::tuple<int32_t> inventorySlot;
    inventorySlot = _inventorySlot;
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, inventorySlot);
}

/* Arma el buffer y lo envia para el evento de atacar a una posicion */
void ClientEventHandler::_processAttack(Coordinate selectedTile) {
    msgpack::type::tuple<GameType::PlayerEvent> event(GameType::PLAYER_ATTACK);
    msgpack::type::tuple<int32_t, int32_t> targetPosition;
    targetPosition = {selectedTile.i, selectedTile.j};
    msgpack::pack(msgBuffer, event);
    msgpack::pack(msgBuffer, targetPosition);
}

/* Envia el mensaje con el evento y su informacion al servidor */
void ClientEventHandler::_sendMessage() {
    std::string aux = msgBuffer.str();
    uint32_t length = htonl(aux.size());
    std::vector<char> buffer(sizeof(uint32_t));
    ClientProtocol::loadBytes(buffer, &length, sizeof(uint32_t));
    std::copy(aux.begin(), aux.end(), std::back_inserter(buffer));
    socket.send(buffer.data(), buffer.size());
    msgBuffer.str(""); /*Reseteo el stringstream*/
    msgBuffer.clear();
}

