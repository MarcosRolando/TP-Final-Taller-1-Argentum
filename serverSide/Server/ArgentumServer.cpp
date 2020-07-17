#include <netdb.h>
#include "ArgentumServer.h"
#include "ServerMonitor.h"
#include "ClientAccepter.h"
#include "../Config/MapFileReader.h"
#include "PlayerManager.h"
#include "../../libs/Timer.h"
#include <unistd.h>

const double  FRAME_TIME = 1/60.f; /*ms que tarda en actualizarse el juego*/
const double TIME_FOR_CLIENTS_INITIALIZATION = 3; //ms dejados para mandarle la data inicial a los clientes
const double BACKUP_TIME = 60; /*5 minutos*/

using namespace std::chrono;

const int MAX_LISTENERS = 10;

void ArgentumServer::finish() {
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
    Timer timeBetweenUpdates, timeBetweenBackups;
    Game game((MapFileReader(mapFilePath)));
    ServerProtocol protocol(game);
    PlayerManager manager(game, protocol, "indexFile", "saveFile");
    ClientsMonitor clients(manager);
    ServerMonitor monitor(*this);
    monitor(); /*Espera la q para cerrar el server*/
    ClientAccepter accepter(clients, protocol, socket, keepRunning, manager);
    accepter(); /*Acepta conexiones de clientes*/

    timeBetweenBackups.start();

    try {
        double lastFrameTime = 0;
        double lastBackupTime = 0;
        while (keepRunning) {
            timeBetweenUpdates.start();
            clients.removeDisconnectedClients(protocol);
            clients.mergeClientsEvents();
            game.update(lastFrameTime, protocol);
            protocol.buildGeneralDataBuffer();
            clients.sendGameUpdate();

            lastFrameTime = timeBetweenUpdates.getTime();
            lastBackupTime = timeBetweenBackups.getTime();
            if (lastBackupTime / 1000 >= BACKUP_TIME) {
                clients.backup();
                timeBetweenBackups.start();
                std::cerr << "backup hecho" << std::endl;
            }
            if (clients.hasWaitingClients() &&
                (FRAME_TIME*1000 - lastFrameTime) > TIME_FOR_CLIENTS_INITIALIZATION) {
                clients.mergeWaitingClients(game, protocol);
            }
            lastFrameTime = timeBetweenUpdates.getTime();
            std::cout << lastFrameTime << std::endl;
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

    finish();
    monitor.join(); /*Joineamos los threads*/
    clients.join();
    accepter.join();
}

ArgentumServer::ArgentumServer() = default;
