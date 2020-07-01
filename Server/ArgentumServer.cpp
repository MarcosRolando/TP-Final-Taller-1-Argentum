#include <sys/socket.h>
#include <netdb.h>
#include <algorithm>
#include "ArgentumServer.h"
#include "ServerMonitor.h"
#include "ClientAccepter.h"
#include "../Config/MapFileReader.h"
#include "PlayerLoader.h"
#include <chrono>
#include <unistd.h>

#define FRAME_TIME 33 /*ms que tarda en actualizarse el juego*/
#define TIME_FOR_CLIENTS_INITIALIZATION 3 //ms dejados para mandarle la data inicial a los clientes

using namespace std::chrono;

const int MAX_LISTENERS = 10;

void ArgentumServer::forceFinish() {
    keepRunning = false;
    socket.close();
}

void ArgentumServer::connect(const std::string& _port, const std::string& mapFilePath) {
    socket.bind(_port);
    socket.maxListen(MAX_LISTENERS);
    _execute(mapFilePath);
}

void ArgentumServer::_execute(const std::string& mapFilePath) {
    Game game((MapFileReader(mapFilePath)), clients);
    ServerProtocol protocol(game.getMap());
    PlayerLoader loader(game, protocol);
    ServerMonitor monitor(*this);
    monitor(); /*Espera la q para cerrar el server*/
    ClientAccepter accepter(clients, protocol, socket, loader, keepRunning);
    accepter(); /*Acepta conexiones de clientes*/

    high_resolution_clock::time_point time1;
    high_resolution_clock::time_point time2;
    duration<double, std::milli> timeStep{};

    double lastFrameTime = 0;
    while (keepRunning) {
        time1 = high_resolution_clock::now();
        game.update(lastFrameTime, protocol);
        protocol.buildGeneralDataBuffer();
        clients.sendGameUpdate();
        //Aca se borran los clientes desconectados

        time2 = high_resolution_clock::now();
        timeStep = time2 - time1;
        lastFrameTime = timeStep.count();
        //std::cout << lastFrameTime << std::endl;
        if ((FRAME_TIME - lastFrameTime) > TIME_FOR_CLIENTS_INITIALIZATION) {
            clients.mergeWaitingClients();
        }
        time2 = high_resolution_clock::now();
        timeStep = time2 - time1;
        lastFrameTime = timeStep.count();
        if (lastFrameTime < FRAME_TIME) {
            usleep((FRAME_TIME - lastFrameTime) * 1000);
            lastFrameTime = FRAME_TIME;
        }
    }

    clients.join();
    monitor.join(); /*Joineamos los threads*/
    accepter.join();
}

ArgentumServer::ArgentumServer() {
    //port = std::move(_port);
    //protocol << game.getMap();
}
