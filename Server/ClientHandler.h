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
#include <msgpack.hpp>

class ServerProtocol;

class ClientHandler;

typedef void (ClientHandler::*processEvent)(std::vector<char>& data);

class ClientHandler : public Thread {
private:
    std::unordered_map<GameType::PlayerEvent, processEvent> eventProcessors;
    Socket socket;
    std::atomic<bool> finished{};
    std::vector<char> buffer;
    std::size_t offset{0};
    msgpack::object_handle handler;
    ServerProtocol& protocol;
    PlayerProxy player;
    std::mutex m;

public:
    ClientHandler(Socket&& socket, ServerProtocol& _protocol);
    ClientHandler(const ClientHandler&) = delete;
    ClientHandler operator=(const ClientHandler&) = delete;

    /*Retorna si el ha terminado de comunicarse con su cliente*/
    bool hasFinished() const;

    void update();

    void sendGameUpdate();

    void sendCurrentGameState(const std::vector<char>& gameState);

    void removePlayer();

    void forceFinish();

    void setPlayerProxy(PlayerProxy&& _player);

    //todo IMPLEMENTAR CONSTRUCTOR POR MOVIMIENTO

private:
    /*Implementa el metodo virtual run de Thread, que sera el metodo ejecutado
    * por el thread*/
    void run() override;
    void _processClientAction(std::vector<char>& data);
    void _processMove(std::vector<char>& data);
    void _processAttack(std::vector<char>& data);
    void _processUseItem(std::vector<char>& data);
    void _processUnequip(std::vector<char>& data);
    void _processPickUp(std::vector<char>& data);
};


#endif //TP3TALLER_CLIENTHANDLER_H
