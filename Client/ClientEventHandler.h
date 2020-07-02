//
// Created by ivan on 26/6/20.
//

#ifndef ARGENTUM_CLIENTEVENTHANDLER_H
#define ARGENTUM_CLIENTEVENTHANDLER_H

#include <SDL.h>
#include "Thread.h"
#include "GameGUI.h"
#include <sstream>
#include "BlockingQueue.hpp"

class Socket;

class ClientEventHandler : public Thread {
private:
    Socket& socket;
    bool& quit;
    GameGUI& game;
    BlockingQueue<std::unique_ptr<SDL_Event>>& events;
    std::stringstream msgBuffer;

public:
    ClientEventHandler(Socket& _socket, bool& quit, GameGUI& game,
                            BlockingQueue<std::unique_ptr<SDL_Event>>& _events)
                        : socket(_socket), quit(quit), game(game), events(_events) {};
    void run() override;

private:
    void _handleMoveKeys(SDL_Event& e);

    void _loadBytes(std::vector<char>& buffer, void* data, unsigned int size);

    void _sendMessage();

    void _handleMouseButtonDown(SDL_Event &e);
};


#endif //ARGENTUM_CLIENTEVENTHANDLER_H