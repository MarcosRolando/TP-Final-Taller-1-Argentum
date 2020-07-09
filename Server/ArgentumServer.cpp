#include <netdb.h>
#include "ArgentumServer.h"
#include "ServerMonitor.h"
#include "ClientAccepter.h"
#include "../Config/MapFileReader.h"
#include "PlayerManager.h"
#include <chrono>
#include <unistd.h>

#define FRAME_TIME 1/60.f /*ms que tarda en actualizarse el juego*/
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
#include <iostream>
void ArgentumServer::_execute(const std::string& mapFilePath) {
    Game game((MapFileReader(mapFilePath)));
    ServerProtocol protocol(game);
    PlayerManager manager(game, protocol, "indexFile", "saveFile");
    ClientsMonitor clients(manager);
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
        clients.removeDisconnectedClients(protocol);
        clients.mergeClientsEvents();
        game.update(lastFrameTime, protocol);
        protocol.buildGeneralDataBuffer();
        clients.sendGameUpdate();

        time2 = high_resolution_clock::now();
        timeStep = time2 - time1;
        lastFrameTime = timeStep.count();
        if (clients.hasWaitingClients() &&
                (FRAME_TIME*1000 - lastFrameTime) > TIME_FOR_CLIENTS_INITIALIZATION) {
            clients.mergeWaitingClients(game, protocol);
        }
        time2 = high_resolution_clock::now();
        timeStep = time2 - time1;
        lastFrameTime = timeStep.count();
        std::cout << lastFrameTime << std::endl;
        if (lastFrameTime < FRAME_TIME*1000) {
            usleep((FRAME_TIME*1000 - lastFrameTime) * 1000);
            lastFrameTime = FRAME_TIME*1000;
        }
    }

    forceFinish();
    monitor.join(); /*Joineamos los threads*/
    clients.join();
    accepter.join();
}

ArgentumServer::ArgentumServer() {
    //port = std::move(_port);
    //protocol << game.getMap();
}
