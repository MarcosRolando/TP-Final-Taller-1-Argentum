#ifndef TP3_SERVER_H
#define TP3_SERVER_H

/*Esta clase se encarga de manejar la
 * logica de las conexiones pero no de la comunicacion con los clientes, de eso
 * se encarga el Client Handler*/

#include "Socket.h"
#include <string>
#include <atomic>
#include <vector>
#include "ClientHandler.h"
#include <memory>
#include <utility>
#include "../Game/Game.h"

class ArgentumServer {
private:
    Game game;
    std::atomic<bool> finished;
    std::string port;
    Socket socket;
    std::vector<std::unique_ptr<ClientHandler>> clients;

public:
    explicit ArgentumServer(std::string&& port) : finished(false), port(std::move(port)) {}
    ArgentumServer(const ArgentumServer&) = delete; /*Borro los constructores por copia*/
    ArgentumServer operator=(const ArgentumServer&) = delete;

    /*Levanta el servidor en el puerto pedido en el constructor*/
    void connect();

    /*Hace que el servidor deje de aceptar nuevos clientes*/
    void forceFinish();

private:
    void _execute();
    void _acceptConnections();
    void _processConnections();
};

#endif //TP3_SERVER_H
