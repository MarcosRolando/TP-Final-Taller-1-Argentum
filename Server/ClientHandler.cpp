#include "ClientHandler.h"

#include <vector>
#include <mutex>
#include "../Entities/PlayerProxy.h"
#include "ServerProtocol.h"
#include "PlayerLoader.h"

#define MAX_NUMBER_OF_MESSAGES_STORED 3

///////////////////////////////PUBLIC///////////////////////////////

ClientHandler::ClientHandler(Game &game, Socket &&socket, ServerProtocol &_protocol, PlayerLoader &_loader) :
        socket(std::move(socket)), protocol(_protocol), loader(_loader), player(game) {
    finished = false;
    hasDataToSend = false;
}

void ClientHandler::run() {
    //PlayerProxy player = loader.getPlayer();
    _sendMapInfoToClient();
    std::vector<char> data = protocol.getCurrentState(player);
    socket.send(data.data(), data.size());

    //std::unique_lock<std::mutex> lk(m);
    //std::vector<char> buffer;

    while (!finished) {
        //socket.receive(buffer, sizeof(unit32_t));

        if (hasDataToSend) {
            _sendUpdateDataToClient();
            hasDataToSend = false;
        }

    }
}

void ClientHandler::_receive(std::vector<char>& message,
                                                unsigned int& bufferLength) {
    /*
    do {
        message = protocol.commandBuffer(bufferLength);
        socket.receive(message.data(), bufferLength);
        protocol.processCommand(message.data());
    } while (!protocol.finishedReceiving());
     */
}

void ClientHandler::_send(std::vector<char>& message,
                                                unsigned int& bufferLength) {
    //essage = protocol.getResponse(bufferLength);
    socket.send(message.data(), bufferLength);
}

bool ClientHandler::hasFinished() const {
    return finished;
}

void ClientHandler::update() {
    std::unique_lock<std::mutex> lk(m);
    player.giveEventsToGame();
}

void ClientHandler::sendUpdateData() {
    hasDataToSend = true;
}

///////////////////////////////PRIVATE///////////////////////////////

void ClientHandler::_sendUpdateDataToClient() {
    const std::vector<char>& generalData = protocol.getGeneralData();
    socket.send(generalData.data(), generalData.size());

    //ACA SE MANDA LA INFORMACION GENERAL DE PLAYER
}

void ClientHandler::_sendMapInfoToClient() {
    const std::vector<char>& mapInfo = protocol.getMapInfo();
    socket.send(mapInfo.data(), mapInfo.size());
}

void ClientHandler::_addMessageToQueue() {
    std::unique_lock<std::mutex> lk(m);
    uint32_t messageLen;
    socket.receive(reinterpret_cast<char *>(&messageLen), sizeof(uint32_t));
    messageLen = ntohl(messageLen);
    std::vector<char> buffer(messageLen);
    socket.receive(buffer.data(), messageLen);
}

void ClientHandler::_storePlayerProxy() {
    uint32_t messageLen;
    socket.receive(reinterpret_cast<char*>(&messageLen), sizeof(uint32_t));
    messageLen = ntohl(messageLen);
    std::vector<char> buffer(messageLen);
    socket.receive(buffer.data(), messageLen);
}


