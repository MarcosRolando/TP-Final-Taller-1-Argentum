//
// Created by agustin on 26/6/20.
//

#include "ClientsMonitor.h"

/*
void ClientsMonitor::pushClient(Socket &&peer, ServerProtocol &protocol) {
    std::lock_guard<std::mutex> lock(mutex);
    clients.emplace_back(new ClientHandler(std::move(peer), protocol));
    (*clients.back())();
}
*/

void ClientsMonitor::join() {
    for (auto & client : clients) {
        client->join();
    }
}

void ClientsMonitor::update() {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto & client : clients) {
        client->update();
    }
}

void ClientsMonitor::pushToWaitingList(Socket &&peer, ServerProtocol &protocol) {
    std::lock_guard<std::mutex> lock(mutex);
    waitingList.emplace_back(new ClientHandler(std::move(peer), protocol));
}

void ClientsMonitor::mergeWaitingClients() {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto & waitingClient: waitingList) {
        clients.push_back(std::move(waitingClient));
        (*clients.back())();
    }
    waitingList.clear();
}
