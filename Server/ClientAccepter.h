//
// Created by marcos on 6/24/20.
//

#ifndef ARGENTUM_CLIENTACCEPTER_H
#define ARGENTUM_CLIENTACCEPTER_H

#include <list>
#include <memory>
#include "Thread.h"
#include <atomic>

class ServerProtocol;
class Socket;
class ClientHandler;
class ClientsMonitor;
class PlayerLoader;

class ClientAccepter : public Thread {
private:
    ClientsMonitor& clients;
    ServerProtocol& protocol;
    Socket& serverSocket;
    PlayerLoader& loader;
    std::atomic<bool>& keepRunning;

public:
    ClientAccepter(ClientsMonitor& _clients, ServerProtocol& _protocol,
                    Socket& _serverSocket, PlayerLoader& _loader, std::atomic<bool>& _keepRunning) :
                    clients(_clients), protocol(_protocol),
                    serverSocket(_serverSocket), loader(_loader), keepRunning(_keepRunning) {}

    void run() override;
};


#endif //ARGENTUM_CLIENTACCEPTER_H
