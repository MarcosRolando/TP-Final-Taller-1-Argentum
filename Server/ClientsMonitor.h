//
// Created by agustin on 26/6/20.
//

#ifndef ARGENTUM_CLIENTSMONITOR_H
#define ARGENTUM_CLIENTSMONITOR_H

#include <memory>
#include <list>
#include "ClientHandler.h"

class ClientsMonitor {
private:
    std::list<std::unique_ptr<ClientHandler>> clients;

public:
    ClientsMonitor(Socket&& accepter);
};


#endif //ARGENTUM_CLIENTSMONITOR_H
