//
// Created by marcos on 6/24/20.
//

#include "ClientAccepter.h"
#include "Socket.h"
#include "ClientHandler.h"

void ClientAccepter::run() {
    while (keepRunning) {
        try {
            Socket peer = serverSocket.accept();
            clients.emplace_back(new ClientHandler(std::move(peer),
                                                                0));
            (*clients.back())();
        } catch(...) {
            //nothing
        }
    }
}
