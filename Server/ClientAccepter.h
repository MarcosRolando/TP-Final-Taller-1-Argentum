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

class ClientAccepter : public Thread {
private:
    std::list<std::unique_ptr<ClientHandler>>& clients;
    ServerProtocol& protocol;
    Socket& serverSocket;
    std::atomic<bool>& keepRunning;

public:
    ClientAccepter(std::list<std::unique_ptr<ClientHandler>>& _clients, ServerProtocol& _protocol,
                    Socket& _serverSocket, std::atomic<bool>& _keepRunning) :
                    clients(_clients), protocol(_protocol),
                    serverSocket(_serverSocket), keepRunning(_keepRunning) {}

    void run() override;
};


#endif //ARGENTUM_CLIENTACCEPTER_H
