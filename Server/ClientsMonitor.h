//
// Created by agustin on 26/6/20.
//

#ifndef ARGENTUM_CLIENTSMONITOR_H
#define ARGENTUM_CLIENTSMONITOR_H

#include <memory>
#include <list>
#include "ClientHandler.h"
#include <mutex>

class ClientsMonitor {
private:
    std::mutex mutex;
    std::list<std::unique_ptr<ClientHandler>> clients;

public:
    void pushClient(Socket&& peer, ServerProtocol& protocol);
    void update();
    void eraseDisconnectedClients();
    void join();
};


#endif //ARGENTUM_CLIENTSMONITOR_H
