//
// Created by agustin on 26/6/20.
//

#include "ClientsMonitor.h"
#include "PlayerLoader.h"
#include "../Game/Game.h"

void ClientsMonitor::join() {
    for (auto & client : clients) {
        client->forceFinish();
        client->join();
    }
}

void ClientsMonitor::mergeClientsEvents() {
    //std::lock_guard<std::mutex> lock(mutex);
    for (auto & client : clients) {
        client->update();
    }
}

void ClientsMonitor::pushToWaitingList(Socket &&peer, ServerProtocol &protocol,
                                    InitialPlayerData&& playerData) {
    std::lock_guard<std::mutex> lock(mutex);
    waitingList.emplace_back(new ClientHandler(std::move(peer), protocol),
                                std::move(playerData));
}

void ClientsMonitor::mergeWaitingClients(Game& game, ServerProtocol& protocol) {
    std::lock_guard<std::mutex> lock(mutex);

    for (auto & waitingClient: waitingList) {
        InitialPlayerData playerData = std::move(std::get<1>(waitingClient)); /*creo los players*/
        std::get<0>(waitingClient)->setPlayerProxy(loader.createPlayer(playerData));
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
    ClientShouldBeRemoved shouldBeRemoved(protocol);
    clients.erase(std::remove_if(clients.begin(), clients.end(),
                                    shouldBeRemoved), clients.end());
}

bool ClientShouldBeRemoved::operator()(std::unique_ptr<ClientHandler> &client) {
    if (client->hasFinished()) {
        client->removePlayer();
        client->join();
        return true;
    } else {
        return false;
    }
}
