//
// Created by agustin on 26/6/20.
//
#ifndef ARGENTUM_CLIENTSMONITOR_H
#define ARGENTUM_CLIENTSMONITOR_H

#include <memory>
#include <list>
#include "ClientHandler.h"
#include <mutex>

class PlayerProxy;

class ClientsMonitor {
private:
    std::mutex mutex;
    std::list<std::unique_ptr<ClientHandler>> clients;
    std::list<std::unique_ptr<ClientHandler>> waitingList;

public:
    void pushToWaitingList(Socket &&peer, ServerProtocol &protocol, PlayerProxy&& player);
    void mergeWaitingClients(const std::vector<char>& gameState);
    void update();
    void eraseDisconnectedClients();
    void sendGameUpdate();
    void join();
    bool hasWaitingClients();
};


#endif //ARGENTUM_CLIENTSMONITOR_H
