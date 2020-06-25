//
// Created by marcos on 6/24/20.
//

#ifndef ARGENTUM_CLIENTACCEPTER_H
#define ARGENTUM_CLIENTACCEPTER_H

#include <vector>
#include <memory>
#include "Thread.h"
#include <atomic>

class Socket;
class ClientHandler;

class ClientAccepter : public Thread {
private:
    std::vector<std::unique_ptr<ClientHandler>>& clients;
    Socket& serverSocket;
    std::atomic<bool>& keepRunning;

public:
    ClientAccepter(std::vector<std::unique_ptr<ClientHandler>>& _clients,
                    Socket& _serverSocket, std::atomic<bool>& _keepRunning) :
                    clients(_clients), serverSocket(_serverSocket), keepRunning(_keepRunning) {}

    void run() override;
};


#endif //ARGENTUM_CLIENTACCEPTER_H
