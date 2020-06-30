#include "ClientHandler.h"

#include <vector>
#include <mutex>
#include "../Entities/PlayerProxy.h"
#include "ServerProtocol.h"
#include "PlayerLoader.h"

#define MAX_NUMBER_OF_MESSAGES_STORED 3

MSGPACK_ADD_ENUM(GameType::PlayerEvent)
MSGPACK_ADD_ENUM(GameType::Direction)

///////////////////////////////PUBLIC///////////////////////////////

ClientHandler::ClientHandler(Socket &&socket, ServerProtocol &_protocol, PlayerLoader &_loader) :
        socket(std::move(socket)), protocol(_protocol), loader(_loader) {
    finished = false;
    hasDataToSend = false;
}

void ClientHandler::run() {
    try {
        uint32_t msgLength = 0;
        player = loader.getPlayer();
        _sendMapInfoToClient();
        std::vector<char> data = protocol.getCurrentState(player);
        socket.send(data.data(), data.size());

        //std::unique_lock<std::mutex> lk(m);
        //std::vector<char> buffer;

        while (!finished) {
            data.clear();
            socket.receive((char*)&(msgLength), sizeof(uint32_t));
            msgLength = ntohl(msgLength);
            data.resize(msgLength);
            socket.receive(data.data(), msgLength);
            _processClientAction(data);
        }

    } catch(...) {

    }
}

void ClientHandler::sendGameUpdate() {
    _sendUpdateDataToClient();
}

void ClientHandler::_processClientAction(std::vector<char>& data) {
    std::size_t offset = 0;
    msgpack::type::tuple<GameType::PlayerEvent> event;
    msgpack::object_handle handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(event);
    if (std::get<0>(event) == GameType::MOVE) {
        msgpack::type::tuple<GameType::Direction> moveInfo;
        handler = msgpack::unpack(data.data(), data.size(), offset);
        handler->convert(moveInfo);
        player.move(std::get<0>(moveInfo));
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

void ClientHandler::update(double timeStep) {
    std::unique_lock<std::mutex> lk(m);
    player.giveEventsToGame(timeStep);
}

///////////////////////////////PRIVATE///////////////////////////////

void ClientHandler::_sendUpdateDataToClient() {
    const std::vector<char>& generalData = protocol.getGeneralData();
    //std::cout << "VOY A MANDAR COSAS " << std::endl;
    if (generalData.size() != sizeof(uint32_t)) {
        socket.send(generalData.data(), generalData.size());
    }

    //ACA SE MANDA LA INFORMACION GENERAL DE PLAYER
}

void ClientHandler::_sendMapInfoToClient() {
    const std::vector<char>& mapInfo = protocol.getMapInfo();
    socket.send(mapInfo.data(), mapInfo.size());
}

void ClientHandler::_addMessageToQueue() {
    uint32_t messageLen;
    socket.receive(reinterpret_cast<char *>(&messageLen), sizeof(uint32_t));
    messageLen = ntohl(messageLen);
    std::vector<char> buffer(messageLen);
    socket.receive(buffer.data(), messageLen);
    std::unique_lock<std::mutex> lk(m);
}

void ClientHandler::_storePlayerProxy() {
    uint32_t messageLen;
    socket.receive(reinterpret_cast<char*>(&messageLen), sizeof(uint32_t));
    messageLen = ntohl(messageLen);
    std::vector<char> buffer(messageLen);
    socket.receive(buffer.data(), messageLen);
    //hacer unpack
}


