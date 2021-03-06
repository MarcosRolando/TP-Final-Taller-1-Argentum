//
// Created by agustin on 26/6/20.
//

#include "ClientsMonitor.h"
#include "PlayerManager.h"
#include "../Game/Game.h"

void ClientsMonitor::join() {
    for (auto & client : clients) {
        client->forceFinish();
        client->join();
    }
}

void ClientsMonitor::mergeClientsEvents() {
    for (auto & client : clients) {
        client->update();
    }
}

void ClientsMonitor::pushToWaitingList(Socket &&peer, ServerProtocol &protocol,
                                       PlayerData&& playerData) {
    std::lock_guard<std::mutex> lock(mutex);
    waitingList.emplace_back(new ClientHandler(std::move(peer), protocol),
                                std::move(playerData));
}

void ClientsMonitor::mergeWaitingClients(Game& game, ServerProtocol& protocol) {
    std::lock_guard<std::mutex> lock(mutex);

    for (auto & waitingClient: waitingList) {
        PlayerData playerData = std::move(std::get<1>(waitingClient)); /*creo los players*/
        std::get<0>(waitingClient)->setPlayerProxy(manager.addPlayer(playerData));
    }

    const std::vector<char>& gameState = game.getCurrentState(protocol); /*armo el buffer*/

    for (auto & waitingClient: waitingList) { /*disparo los nuevos client handlers*/
        clients.push_back(std::move(std::get<0>(waitingClient)));
        (*clients.back()).sendCurrentGameState(gameState);
        (*clients.back())();
    }
    waitingList.clear();
}

void ClientsMonitor::sendGameUpdate() {
    for (const auto& client : clients) {
        client->sendGameUpdate();
    }
}

bool ClientsMonitor::hasWaitingClients() {
    return !waitingList.empty();
}

void ClientsMonitor::removeDisconnectedClients(ServerProtocol& protocol) {
    ClientShouldBeRemoved shouldBeRemoved(protocol, manager);
    clients.erase(std::remove_if(clients.begin(), clients.end(),
                                    shouldBeRemoved), clients.end());
}

void ClientsMonitor::backup() {
    for (auto & client : clients) {
        PlayerData dataToStore = client->getPlayerData();
        manager.storeOldPlayer(dataToStore);
    }
}

bool ClientShouldBeRemoved::operator()(std::unique_ptr<ClientHandler> &client) {
    if (client->hasFinished()) {
        PlayerData dataToStore = client->getPlayerData();
        manager.storeOldPlayer(dataToStore);
        manager.removePlayer(dataToStore.nickname);
        client->join();
        return true;
    } else {
        return false;
    }
}
