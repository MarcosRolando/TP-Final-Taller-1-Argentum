#include <sys/socket.h>
#include <netdb.h>
#include <algorithm>
#include "ArgentumServer.h"
#include "ClientHandler.h"
#include "ServerMonitor.h"
#include "../TPException.h"
#include <chrono>
#include <atomic>
#include <unistd.h>
#include <iostream>

#define FRAME_TIME 33 /*ms que tarda en actualizarse el juego*/

using namespace std::chrono;

const int MAX_LISTENERS = 10;

/*Funcion que le paso a remove_if para que verifique si termino el cliente*/
bool clientHasFinished(std::unique_ptr<ClientHandler>& client) {
    if (client->hasFinished()) {
        client->join();
        return true;
    }
    return false;
}

void ArgentumServer::_acceptConnections() {
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

void ArgentumServer::_processConnections() {
    ServerMonitor monitor(*this);
    monitor();
    _acceptConnections();
    for (auto & client : clients) {
        client->join();
    }
    monitor.join();
}

void ArgentumServer::forceFinish() {
    finished = true;
    socket.close();
}

void ArgentumServer::connect() {
    socket.bind(port);
    socket.maxListen(MAX_LISTENERS);
    _processConnections();
}

void ArgentumServer::_execute() {
    std::atomic<bool> keepRunning(true);

    //ACA SE TIRA THREAD PARA RECIBIR LA Q QUE CIERRA EL SERVER

    high_resolution_clock::time_point time1;
    high_resolution_clock::time_point time2;
    duration<double, std::milli> timeStep{};
    double lastFrameTime = 0;
    while (keepRunning) {
        time1 = high_resolution_clock::now();

        game.update(lastFrameTime);

        time2 = high_resolution_clock::now();
        timeStep = time2 - time1;
        lastFrameTime = timeStep.count();
        std::cout << lastFrameTime << std::endl;
        if (lastFrameTime < FRAME_TIME) {
            usleep((FRAME_TIME - lastFrameTime) * 1000);
            lastFrameTime = FRAME_TIME;
        }
    }
}
