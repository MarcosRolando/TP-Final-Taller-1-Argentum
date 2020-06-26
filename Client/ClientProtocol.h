//
// Created by ivan on 24/6/20.
//

#ifndef ARGENTUM_CLIENTPROTOCOL_H
#define ARGENTUM_CLIENTPROTOCOL_H

#include "GameGUI.h"
#include "../Shared/GameEnums.h"


class Socket;

class ClientProtocol {
private:
    //GameGUI game;
    Socket& socket;

public:
    explicit ClientProtocol(Socket& _socket) : socket(_socket){}
    void receiveMapInfo(GameGUI& game);
};


#endif //ARGENTUM_CLIENTPROTOCOL_H
