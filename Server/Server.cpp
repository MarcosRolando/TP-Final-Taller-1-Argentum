#include <sys/socket.h>
#include <netdb.h>
#include <algorithm>
#include "Server.h"
#include "ClientHandler.h"
#include "ServerMonitor.h"
#include "../TPException.h"

const int MAX_LISTENERS = 10;

/*Funcion que le paso a remove_if para que verifique si termino el cliente*/
bool clientHasFinished(std::unique_ptr<ClientHandler>& client) {
    if (client->hasFinished()) {
        client->join();
        return true;
    }
    return false;
}

void Server::_acceptConnections() {
    //unsigned int secretNumber;
    while (!finished) {
        try {
            Socket peer = socket.accept();
            /*
            secretNumber = file.getNextNumber();
            clients.emplace_back(new ClientHandler(std::move(peer),
                                                                secretNumber));
                                                                */
            (*clients.back())();
            clients.erase(std::remove_if(clients.begin(),
                    clients.end(), clientHasFinished), clients.end());
        } catch(TPException& e) {
            if (!finished) throw e; /*Hubo un error externo*/
        }
    }
}

void Server::_processConnections() {
    ServerMonitor monitor(*this);
    monitor();
    _acceptConnections();
    for (auto & client : clients) {
        client->join();
    }
    monitor.join();
}

void Server::forceFinish() {
    finished = true;
    socket.close();
}

void Server::connect() {
    socket.bind(port);
    socket.maxListen(MAX_LISTENERS);
    _processConnections();
}
