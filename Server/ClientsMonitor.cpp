//
// Created by agustin on 26/6/20.
//

#include "ClientsMonitor.h"

void ClientsMonitor::join() {
    for (auto & client : clients) {
        client->forceFinish();
        client->join();
    }
}

void ClientsMonitor::update() {
    //std::lock_guard<std::mutex> lock(mutex);
    for (auto & client : clients) {
        client->update();
    }
}

void ClientsMonitor::pushToWaitingList(Socket &&peer, ServerProtocol &protocol, PlayerProxy&& player) {
    std::lock_guard<std::mutex> lock(mutex);
    waitingList.emplace_back(new ClientHandler(std::move(peer), protocol, std::move(player)));
}

void ClientsMonitor::mergeWaitingClients(const std::vector<char>& gameState) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto & waitingClient: waitingList) {
        clients.push_back(std::move(waitingClient));
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
