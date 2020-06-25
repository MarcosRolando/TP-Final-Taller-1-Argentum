//
// Created by ivan on 24/6/20.
//

#ifndef ARGENTUM_CLIENTPROTOCOL_H
#define ARGENTUM_CLIENTPROTOCOL_H

#include "GameGUI.h"

class Socket;

class ClientProtocol {
private:
    GameGUI game;
    Socket& socket;

public:
    explicit ClientProtocol(Socket& _socket) : socket(_socket) {}
    void receiveMapInfo();
};


#endif //ARGENTUM_CLIENTPROTOCOL_H
