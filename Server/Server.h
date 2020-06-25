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

class Server {
private:
    std::atomic<bool> finished;
    std::string port;
    Socket socket;
    std::vector<std::unique_ptr<ClientHandler>> clients;

public:
    Server(std::string&& port, std::string&& fileName) : finished(false),
                            port(std::move(port)) {}
    Server(const Server&) = delete; /*Borro los constructores por copia*/
    Server operator=(const Server&) = delete;

    /*Levanta el servidor en el puerto pedido en el constructor*/
    void connect();

    /*Hace que el servidor deje de aceptar nuevos clientes*/
    void forceFinish();

private:
    void _acceptConnections();
    void _processConnections();
};

#endif //TP3_SERVER_H
