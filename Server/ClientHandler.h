#ifndef TP3TALLER_CLIENTHANDLER_H
#define TP3TALLER_CLIENTHANDLER_H

/*Esta clase se comunica con el cliente, es decir, el servidor
 * cuando acepta a un cliente crea un nuevo ClientHandler (un estilo de
 * subservidor) y lo dispara en un nuevo thread. Esta clase guarda una instancia
 * del protocolo, que guarda una instancia independiente del Juego de Adivinar
 * el Numero*/
#include "Socket.h"
#include "Thread.h"
#include "../Entities/PlayerProxy.h"
#include <queue>
#include <vector>
#include <mutex>
#include <utility>
#include <atomic>

class ServerProtocol;
class PlayerLoader;

class ClientHandler : public Thread {
private:
    Socket socket;
    std::atomic<bool> finished;
    std::atomic<bool> hasDataToSend;
    ServerProtocol& protocol;
    PlayerLoader& loader;
    PlayerProxy player;
    std::mutex m;

public:
    ClientHandler(Socket&& socket, ServerProtocol& _protocol, PlayerLoader& _loader);
    ClientHandler(const ClientHandler&) = delete;
    ClientHandler operator=(const ClientHandler&) = delete;

    /*Retorna si el ha terminado de comunicarse con su cliente*/
    bool hasFinished() const;

    void update(double timeStep);

    void sendGameUpdate();

    //todo IMPLEMENTAR CONSTRUCTOR POR MOVIMIENTO

private:
    /*Implementa el metodo virtual run de Thread, que sera el metodo ejecutado
    * por el thread*/
    void run() override;
    void _receive(std::vector<char>& message, unsigned int& bufferLength);
    void _send(std::vector<char>& message, unsigned int& bufferLength);
    void _sendMapInfoToClient();
    void _sendUpdateDataToClient();
    void _addMessageToQueue();
    void _storePlayerProxy();
    void _processClientAction(std::vector<char>& data);
};


#endif //TP3TALLER_CLIENTHANDLER_H
