//
// Created by ivan on 26/6/20.
//

#ifndef ARGENTUM_CLIENTEVENTHANDLER_H
#define ARGENTUM_CLIENTEVENTHANDLER_H

#include <SDL.h>
#include "Thread.h"
#include "GameGUI.h"
#include <sstream>

class EventBlockingQueue;
class Socket;

class ClientEventHandler : public Thread {
private:
    Socket& socket;
    bool& quit;
    GameGUI& game;
    EventBlockingQueue& events;
    std::stringstream msgBuffer;

public:
    ClientEventHandler(Socket& _socket, bool& quit, GameGUI& game, EventBlockingQueue& _events)
                        : socket(_socket), quit(quit), game(game), events(_events) {};
    void run() override;

private:
    void _handleMoveKeys(SDL_Event& e);

    void _loadBytes(std::vector<char>& buffer, void* data, unsigned int size);

    void _sendMessage();
};


#endif //ARGENTUM_CLIENTEVENTHANDLER_H
