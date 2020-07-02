#include "ClientHandler.h"
#include <vector>
#include <mutex>
#include "ServerProtocol.h"
#include "PlayerLoader.h"
#include <iostream>
#include "../TPException.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)
MSGPACK_ADD_ENUM(GameType::Race)
MSGPACK_ADD_ENUM(GameType::Class)
MSGPACK_ADD_ENUM(GameType::Direction)

///////////////////////////////PUBLIC///////////////////////////////

ClientHandler::ClientHandler(Socket &&socket, ServerProtocol &_protocol, PlayerLoader &_loader) :
        socket(std::move(socket)), protocol(_protocol), loader(_loader) {
}

void ClientHandler::run() {
    try {
        _receivePlayerInfo();
        uint32_t msgLength = 0;
        _sendMapInfoToClient();

        while (!finished) {
            buffer.clear();
            socket.receive((char*)&(msgLength), sizeof(uint32_t));
            msgLength = ntohl(msgLength);
            buffer.resize(msgLength);
            socket.receive(buffer.data(), msgLength);
            _processClientAction(buffer);
        }

    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void ClientHandler::sendGameUpdate() {
    _sendUpdateDataToClient();
}

void ClientHandler::_processClientAction(std::vector<char>& data) {
    offset = 0;
    msgpack::type::tuple<GameType::PlayerEvent> event;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(event);
    if (std::get<0>(event) == GameType::MOVE) {
        msgpack::type::tuple<GameType::Direction> moveInfo;
        handler = msgpack::unpack(data.data(), data.size(), offset);
        handler->convert(moveInfo);
        player.move(std::get<0>(moveInfo));
    }
}

bool ClientHandler::hasFinished() const {
    return finished;
}

void ClientHandler::update() {
    std::unique_lock<std::mutex> lk(m);
    player.giveEventsToGame();
}

///////////////////////////////PRIVATE///////////////////////////////

void ClientHandler::_sendUpdateDataToClient() {
    const std::vector<char>& generalData = protocol.getGeneralData();
    if (generalData.size() != sizeof(uint32_t)) {
        socket.send(generalData.data(), generalData.size());
    }

    //ACA SE MANDA LA INFORMACION GENERAL DE PLAYER
}

void ClientHandler::_sendMapInfoToClient() {
    const std::vector<char>& mapInfo = protocol.getMapInfo();
    socket.send(mapInfo.data(), mapInfo.size());
    buffer = protocol.getCurrentState(player);
    socket.send(buffer.data(), buffer.size());
}

void ClientHandler::_addMessageToQueue() {
    uint32_t messageLen;
    socket.receive(reinterpret_cast<char *>(&messageLen), sizeof(uint32_t));
    messageLen = ntohl(messageLen);
    buffer.clear();
    buffer.resize(messageLen);
    socket.receive(buffer.data(), messageLen);
    std::unique_lock<std::mutex> lk(m);
    //todo procesar el mensaje al proxy
}

void ClientHandler::_receivePlayerInfo() {
    offset = 0;
    uint32_t msgLen;
    socket.receive(reinterpret_cast<char*>(&msgLen), sizeof(uint32_t));
    msgLen = ntohl(msgLen);
    buffer.clear();
    buffer.resize(msgLen);
    socket.receive(buffer.data(), msgLen);
    msgpack::type::tuple<GameType::PlayerEvent> creationID;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(creationID);
    if (std::get<0>(creationID) == GameType::CREATE_PLAYER) {
        _createPlayer();
    } else if (std::get<0>(creationID) == GameType::LOAD_PLAYER) {
        //_loadPlayer();
    } else {
        throw TPException("No me llego ni mensaje de creacion ni de carga de player!");
    }
}

void ClientHandler::_createPlayer() {
    msgpack::type::tuple<std::string, GameType::Race, GameType::Class> info;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(info);
    player = loader.createPlayer(std::move(std::get<0>(info)),
                        std::get<1>(info), std::get<2>(info));
}
