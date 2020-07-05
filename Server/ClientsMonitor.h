//
// Created by agustin on 26/6/20.
//
#ifndef ARGENTUM_CLIENTSMONITOR_H
#define ARGENTUM_CLIENTSMONITOR_H

#include <memory>
#include <list>
#include "ClientHandler.h"
#include <mutex>
#include "InitialPlayerData.h"

class PlayerProxy;
class PlayerLoader;
class Game;
class ServerProtocol;

class ClientShouldBeRemoved {
private:
    ServerProtocol& protocol;

public:
    explicit ClientShouldBeRemoved(ServerProtocol& _protocol) : protocol(_protocol) {}
    bool operator()(std::unique_ptr<ClientHandler>& client);
};

class ClientsMonitor {
private:
    std::mutex mutex;
    std::list<std::unique_ptr<ClientHandler>> clients;
    std::list<std::tuple<std::unique_ptr<ClientHandler>, InitialPlayerData>> waitingList;
    PlayerLoader& loader;

public:
    explicit ClientsMonitor(PlayerLoader& _loader) : loader(_loader) {}
    void pushToWaitingList(Socket &&peer, ServerProtocol &protocol, InitialPlayerData&& playerData);
    void mergeWaitingClients(Game& game, ServerProtocol& protocol);
    void mergeClientsEvents();
    void removeDisconnectedClients(ServerProtocol& protocol);
    void sendGameUpdate();
    void join();
    bool hasWaitingClients();
};


#endif //ARGENTUM_CLIENTSMONITOR_H
