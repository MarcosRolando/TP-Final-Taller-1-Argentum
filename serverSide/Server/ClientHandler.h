#ifndef TP3TALLER_CLIENTHANDLER_H
#define TP3TALLER_CLIENTHANDLER_H

/*Esta clase se comunica con el cliente, es decir, el servidor
 * cuando acepta a un cliente crea un nuevo ClientHandler (un estilo de
 * subservidor) y lo dispara en un nuevo thread. Esta clase guarda una instancia
 * del protocolo, que guarda una instancia independiente del Juego de Adivinar
 * el Numero*/
#include "../../libs/Socket.h"
#include "../../libs/Thread.h"
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

    //Retorna true si el socket ha terminado de comunicarse con su cliente
    bool hasFinished() const;

    //Le delega a PlayerProxy el otorgamiento de los eventos encolados a Game
    void update();

    //Envia toda la informacion del ultimo update del juego
    void sendGameUpdate();

    //Envia el estado inicial del juego
    void sendCurrentGameState(const std::vector<char>& gameState);

    //Cierra el socket y fuerza a que termine de ejecutarse el thread
    //que recibe los comandos del cliente
    void forceFinish();

    //Se apropia del PlayerProxy recibido
    void setPlayerProxy(PlayerProxy&& _player);

    //Retorna los datos actuales del jugador del cliente
    PlayerData getPlayerData() const;

private:
    /*Implementa el metodo virtual run de Thread, que sera el metodo ejecutado
    * por el thread*/
    void run() override;
    void _processClientAction(std::vector<char>& data);
    //void _processMove(std::vector<char>& data);
    void _processAttack(std::vector<char>& data);
    void _processUseItem(std::vector<char>& data);
    void _processUnequip(std::vector<char>& data);
    void _processPickUp(std::vector<char>& data);
    void _processDrop(std::vector<char>& data);
    void _processList(std::vector<char>& data);
    void _processBuy(std::vector<char>& data);
    void _processSell(std::vector<char>& data);
    void _processWithdraw(std::vector<char>& data);
    void _processDeposit(std::vector<char>& data);
    void _processMeditate(std::vector<char>& data);
    void _processResurrect(std::vector<char>& data);
    void _processMessage(std::vector<char>& data);
    void _processHeal(std::vector<char>& data);
    void _processInventoryNames(std::vector<char>& data);
    void _processStartMoving(std::vector<char>& data);
    void _processStopMoving(std::vector<char>& data);
};


#endif //TP3TALLER_CLIENTHANDLER_H
