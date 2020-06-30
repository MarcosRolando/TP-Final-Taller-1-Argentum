//
// Created by marcos on 6/24/20.
//

#include "ClientAccepter.h"
#include "Socket.h"
#include "ClientHandler.h"
#include "ClientsMonitor.h"
#include <iostream>

void ClientAccepter::run() {
    while (keepRunning) {
        try {
            Socket peer = serverSocket.accept();
            clients.pushToWaitingList(std::move(peer), protocol, loader);
        } catch(std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
