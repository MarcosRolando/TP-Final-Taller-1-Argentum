#include <netdb.h>
#include "ArgentumServer.h"
#include "ServerMonitor.h"
#include "ClientAccepter.h"
#include "../Config/MapFileReader.h"
#include "PlayerManager.h"
#include "../../libs/Timer.h"
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
    Timer timer;
    Game game((MapFileReader(mapFilePath)));
    ServerProtocol protocol(game);
    PlayerManager manager(game, protocol, "indexFile", "saveFile");
    ClientsMonitor clients(manager);
    ServerMonitor monitor(*this);
    monitor(); /*Espera la q para cerrar el server*/
    ClientAccepter accepter(clients, protocol, socket, keepRunning, manager);
    accepter(); /*Acepta conexiones de clientes*/

    try {
        double lastFrameTime = 0;
        while (keepRunning) {
            timer.start();
            clients.removeDisconnectedClients(protocol);
            clients.mergeClientsEvents();
            game.update(lastFrameTime, protocol);
            protocol.buildGeneralDataBuffer();
            clients.sendGameUpdate();

            lastFrameTime = timer.getTime();
            if (clients.hasWaitingClients() &&
                (FRAME_TIME*1000 - lastFrameTime) > TIME_FOR_CLIENTS_INITIALIZATION) {
                clients.mergeWaitingClients(game, protocol);
            }
            lastFrameTime = timer.getTime();
            //std::cout << lastFrameTime << std::endl;
            if (lastFrameTime < FRAME_TIME*1000) {
                usleep((FRAME_TIME*1000 - lastFrameTime) * 1000);
                lastFrameTime = FRAME_TIME*1000;
            }
        }

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en el main loop!" << std::endl;
    }

    forceFinish();
    monitor.join(); /*Joineamos los threads*/
    clients.join();
    accepter.join();
}

ArgentumServer::ArgentumServer() {
}
