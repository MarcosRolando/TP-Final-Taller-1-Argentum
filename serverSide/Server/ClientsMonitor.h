//
// Created by agustin on 26/6/20.
//
#ifndef ARGENTUM_CLIENTSMONITOR_H
#define ARGENTUM_CLIENTSMONITOR_H

#include <memory>
#include <list>
#include "ClientHandler.h"
#include <mutex>
#include "PlayerData.hpp"

class PlayerProxy;
class PlayerManager;
class Game;
class ServerProtocol;

class ClientShouldBeRemoved {
private:
    ServerProtocol& protocol;
    PlayerManager& manager;

public:
    explicit ClientShouldBeRemoved(ServerProtocol& _protocol, PlayerManager& _manager)
                                : protocol(_protocol), manager(_manager) {}
    bool operator()(std::unique_ptr<ClientHandler>& client);
};

class ClientsMonitor {
private:
    std::mutex mutex;
    std::list<std::unique_ptr<ClientHandler>> clients;
    std::list<std::tuple<std::unique_ptr<ClientHandler>, PlayerData>> waitingList;
    PlayerManager& manager;

public:
    explicit ClientsMonitor(PlayerManager& _manager) : manager(_manager) {}
    void pushToWaitingList(Socket &&peer, ServerProtocol &protocol, PlayerData&& playerData);
    void mergeWaitingClients(Game& game, ServerProtocol& protocol);
    void mergeClientsEvents();
    void removeDisconnectedClients(ServerProtocol& protocol);
    void sendGameUpdate();
    void join();
    bool hasWaitingClients();
    void backup();
};


#endif //ARGENTUM_CLIENTSMONITOR_H
