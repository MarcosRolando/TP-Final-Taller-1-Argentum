//
// Created by ivan on 26/6/20.
//

#ifndef ARGENTUM_CLIENTEVENTHANDLER_H
#define ARGENTUM_CLIENTEVENTHANDLER_H

#include <SDL.h>
#include "../../libs/Thread.h"
#include "GameGUI.h"
#include <sstream>
#include "BlockingQueue.hpp"
#include "InputCommands/CommandVerifier.h"

class Socket;

/*Esta clase procesa los eventos del player y los envia al server acorde
 * al protocolo correspondiente*/

class ClientEventHandler : public Thread {
private:
    Socket& socket;
    bool& quit;
    GameGUI& game;
    CommandVerifier cmdVerifier;
    BlockingQueue<std::unique_ptr<SDL_Event>>& events;
    std::stringstream msgBuffer;

public:
    ClientEventHandler(Socket& _socket, bool& quit, GameGUI& game,
                            BlockingQueue<std::unique_ptr<SDL_Event>>& _events)
                        : socket(_socket), quit(quit), game(game), events(_events) {};

    void run() override;

private:
    void _handleKeyDown(SDL_Event& e);
    void _sendMessage();
    void _handleMouseButtonDown(SDL_Event &e);
    void _processAttack(Coordinate coordinate);
    void _processUseItem(int _inventorySlot);
    void _processUnequipItem(GameType::EquipmentPlace _equipment);
    void _processCommandInput();
    void _handleKeyUp(SDL_Event& e);
};


#endif //ARGENTUM_CLIENTEVENTHANDLER_H
