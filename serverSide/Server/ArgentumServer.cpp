#include <netdb.h>
#include "ArgentumServer.h"
#include "ServerMonitor.h"
#include "ClientAccepter.h"
#include "../Config/MapFileReader.h"
#include "PlayerManager.h"
#include "../Config/Configuration.h"
#include <unistd.h>
#include <iostream>

const double  FRAME_TIME = 1/60.f; /*ms que tarda en actualizarse el juego*/
const double TIME_FOR_CLIENTS_INITIALIZATION = 3; //ms dejados para mandarle la data inicial a los clientes
const double BACKUP_TIME = 5*60; /*5 minutos*/

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

void ArgentumServer::_execute(const std::string& mapFilePath) {
    Timer timeBetweenUpdates, timeBetweenBackups;
    Game game((MapFileReader(mapFilePath)));
    ServerProtocol protocol(game);
    Configuration& config = Configuration::getInstance();
    PlayerManager manager(game, protocol, config.configIndexPath(), config.configSavePath());
    ClientsMonitor clients(manager);
    ServerMonitor monitor(*this);
    monitor(); /*Espera la q para cerrar el server*/
    ClientAccepter accepter(clients, protocol, socket, keepRunning, manager);
    accepter(); /*Acepta conexiones de clientes*/

    timeBetweenBackups.start();

    try {
        double lastFrameTime = 0;
        double lastBackupTime;
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
                std::cout << "Backuped players. Next backup in 5 minutes" << std::endl;
            }
            if (clients.hasWaitingClients() &&
                (FRAME_TIME*1000 - lastFrameTime) > TIME_FOR_CLIENTS_INITIALIZATION) {
                clients.mergeWaitingClients(game, protocol);
            }
            lastFrameTime = timeBetweenUpdates.getTime();
            if (lastFrameTime < FRAME_TIME*1000) {
                usleep((FRAME_TIME*1000 - lastFrameTime) * 1000);
                lastFrameTime = FRAME_TIME*1000;
            }
        }

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Uknown error in Main Game Loop!" << std::endl;
    }

    try {
        if (monitor.closeRequest()) {
            clients.backup();
        }
    } catch (std::exception& e) {
        std::cerr << e.what()  << "while backing up players!" << std::endl;
    } catch (...) {
        std::cerr << "Uknown error while backing up players!" << std::endl;
    }

    finish();
    monitor.join(); /*Joineamos los threads*/
    clients.join();
    accepter.join();
}

ArgentumServer::ArgentumServer() = default;
