//
// Created by marcos on 6/24/20.
//

#include "ClientAccepter.h"
#include "Socket.h"
#include "ClientHandler.h"
#include "ClientsMonitor.h"

void ClientAccepter::run() {
    while (keepRunning) {
        try {
            Socket peer = serverSocket.accept();
            clients.pushToWaitingList(std::move(peer), protocol);
        } catch(...) {
            //nothing
        }
    }
}
