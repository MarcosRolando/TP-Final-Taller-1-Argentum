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

class ClientEventHandler : public Thread {
private:
    bool& quit;
    GameGUI& game;
    EventBlockingQueue& events;
    std::stringstream msgBuffer;

public:
    ClientEventHandler(bool& quit, GameGUI& game, EventBlockingQueue& _events)
                        : quit(quit), game(game), events(_events) {};
    void run() override;

    void _handleMoveKeys(SDL_Event& e);
};


#endif //ARGENTUM_CLIENTEVENTHANDLER_H
