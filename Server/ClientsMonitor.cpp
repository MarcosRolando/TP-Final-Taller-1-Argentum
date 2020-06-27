//
// Created by agustin on 26/6/20.
//

#include "ClientsMonitor.h"

void ClientsMonitor::pushClient(Socket &&peer, ServerProtocol &protocol) {
    std::lock_guard<std::mutex> lock(mutex);
    clients.emplace_back(new ClientHandler(std::move(peer), protocol));
    (*clients.back())();
}

void ClientsMonitor::join() {
    for (auto & client : clients) {
        client->join();
    }
}

void ClientsMonitor::update() {
    for (auto & client : clients) {
        client->update();
    }
}
