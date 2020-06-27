//
// Created by ivan on 26/6/20.
//

#ifndef ARGENTUM_CLIENTEVENTHANDLER_H
#define ARGENTUM_CLIENTEVENTHANDLER_H

#include <SDL.h>
#include "Thread.h"
#include "GameGUI.h"

class ClientEventHandler : public Thread{
private:
    bool& quit;//Ver si dejo esto aca
    GameGUI& game;
public:
    ClientEventHandler(bool& quit, GameGUI& game) : quit(quit), game(game){};
    void run() override;
    ~ClientEventHandler();
};


#endif //ARGENTUM_CLIENTEVENTHANDLER_H
