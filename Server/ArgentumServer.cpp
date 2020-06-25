#include <sys/socket.h>
#include <netdb.h>
#include <algorithm>
#include "ArgentumServer.h"
#include "ServerMonitor.h"
#include "ClientAccepter.h"
#include <chrono>
#include <unistd.h>
#include <iostream>

#define FRAME_TIME 33 /*ms que tarda en actualizarse el juego*/

using namespace std::chrono;

const int MAX_LISTENERS = 10;

void ArgentumServer::forceFinish() {
    keepRunning = false;
    socket.close();
}

void ArgentumServer::connect() {
    socket.bind(port);
    socket.maxListen(MAX_LISTENERS);
    _execute();
}

void ArgentumServer::_execute() {
    ServerMonitor monitor(*this);
    monitor(); /*Espera la q para cerrar el server*/
    ClientAccepter accepter(clients, protocol, socket, keepRunning);
    accepter(); /*Acepta conexiones de clientes*/

    high_resolution_clock::time_point time1;
    high_resolution_clock::time_point time2;
    duration<double, std::milli> timeStep{};

    double lastFrameTime = 0;
    while (keepRunning) {
        time1 = high_resolution_clock::now();

        game.update(lastFrameTime);
        //protocol.notifyClients();

        time2 = high_resolution_clock::now();
        timeStep = time2 - time1;
        lastFrameTime = timeStep.count();
        //std::cout << lastFrameTime << std::endl;
        if (lastFrameTime < FRAME_TIME) {
            usleep((FRAME_TIME - lastFrameTime) * 1000);
            lastFrameTime = FRAME_TIME;
        }
    }

    for (auto & client : clients) {
        client->join();
    }
    monitor.join(); /*Joineamos los threads*/
    accepter.join();
}

ArgentumServer::ArgentumServer(std::string &&_port) {
    port = std::move(_port);
    protocol << game.getMap();
}
