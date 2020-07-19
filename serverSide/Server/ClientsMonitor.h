//
// Created by agustin on 26/6/20.
//
#ifndef ARGENTUM_CLIENTSMONITOR_H
#define ARGENTUM_CLIENTSMONITOR_H

#include <memory>
#include <list>
#include "ClientHandler.h"
#include <mutex>
#include "PlayerData.hpp"

class PlayerProxy;
class PlayerManager;
class Game;
class ServerProtocol;

//Clase functor que se usa para saber cuando un cliente debe ser removido en la
//lista de clientes de ClientsMonitor
class ClientShouldBeRemoved {
private:
    ServerProtocol& protocol;
    PlayerManager& manager;

public:
    explicit ClientShouldBeRemoved(ServerProtocol& _protocol, PlayerManager& _manager)
                                : protocol(_protocol), manager(_manager) {}

    //Si el cliente termino de ejecutarse (si se desconecta) guarda su informacion
    //en el archivo de persistencia, espera a que termine la ejecucion del thread,
    //y delega a PlayerProxy la eliminacion de este de la logica del juego
    bool operator()(std::unique_ptr<ClientHandler>& client);
};

//Clase que se encarga de proteger la lista de clientes frente a posibles race
//conditions
class ClientsMonitor {
private:
    std::mutex mutex;
    std::list<std::unique_ptr<ClientHandler>> clients;
    std::list<std::tuple<std::unique_ptr<ClientHandler>, PlayerData>> waitingList;
    PlayerManager& manager;

public:
    explicit ClientsMonitor(PlayerManager& _manager) : manager(_manager) {}

    //Agrega un ClientHandler a la lista de espera de los nuevos jugadores conectados,
    //para que terminen de agregarse al juego se debe hacer un merge
    void pushToWaitingList(Socket &&peer, ServerProtocol &protocol, PlayerData&& playerData);

    //Crea el PlayerProxy y Player de cada client handler y se lo asigna, mandandole luego
    //el estado actual de juego actual y agregandolo a la lista de clientes activos para
    //cada cliente en la lista de espera
    //Resetea la lista de espera
    void mergeWaitingClients(Game& game, ServerProtocol& protocol);

    //Llama a update para cada cliente (ClientHandler) activo
    void mergeClientsEvents();

    //Elimina todos los jugadores desconectados de la lista de clientes activos
    void removeDisconnectedClients(ServerProtocol& protocol);

    //Envia a todos los clientes activos la informacion del update
    void sendGameUpdate();

    //Fuerza el cierre de todos los clientes y espera a que sus threads
    //terminen de ser ejecutados
    void join();

    //Indica si tiene clientes en la lista de espera, retorna true si es el caso,
    //sino retorna false
    bool hasWaitingClients();

    //Guarda la informacion actual de todos los players activos en el archivo de
    //persistencia
    void backup();
};


#endif //ARGENTUM_CLIENTSMONITOR_H
