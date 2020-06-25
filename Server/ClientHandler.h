#ifndef TP3TALLER_CLIENTHANDLER_H
#define TP3TALLER_CLIENTHANDLER_H

/*Esta clase se comunica con el cliente, es decir, el servidor
 * cuando acepta a un cliente crea un nuevo ClientHandler (un estilo de
 * subservidor) y lo dispara en un nuevo thread. Esta clase guarda una instancia
 * del protocolo, que guarda una instancia independiente del Juego de Adivinar
 * el Numero*/

#include "ServerProtocol.h"
#include "Socket.h"
#include "Thread.h"
#include <vector>
#include <utility>
#include <atomic>

class ClientHandler : public Thread {
private:
    Socket socket;
    ServerProtocol protocol;
    std::atomic<bool> finished;

public:
    ClientHandler(Socket&& socket, unsigned int secretNumber) :
        socket(std::move(socket)), finished(false) {}
    ClientHandler(const ClientHandler&) = delete;
    ClientHandler operator=(const ClientHandler&) = delete;

    /*Retorna si el ha terminado de comunicarse con su cliente*/
    bool hasFinished() const;

private:
    /*Implementa el metodo virtual run de Thread, que sera el metodo ejecutado
    * por el thread*/
    void run() override;
    void _receive(std::vector<char>& message, unsigned int& bufferLength);
    void _send(std::vector<char>& message, unsigned int& bufferLength);
};


#endif //TP3TALLER_CLIENTHANDLER_H
