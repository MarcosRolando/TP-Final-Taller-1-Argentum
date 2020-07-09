//
// Created by marcos on 6/24/20.
//

#include "ClientAccepter.h"
#include "Socket.h"
#include "ClientHandler.h"
#include "ClientsMonitor.h"
#include <iostream>
#include "../TPException.h"
#include "PlayerLoader.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)
MSGPACK_ADD_ENUM(GameType::Class)
MSGPACK_ADD_ENUM(GameType::Race)

void ClientAccepter::run() {
    while (keepRunning) {
        try {
            Socket clientSocket = serverSocket.accept();
            PlayerData playerData = _receivePlayerInfo(clientSocket);
            clients.pushToWaitingList(std::move(clientSocket), protocol, std::move(playerData));
        } catch(std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

PlayerData ClientAccepter::_receivePlayerInfo(Socket& clientSocket) {
    std::size_t offset = 0;
    std::vector<char> buffer;
    uint32_t msgLen;
    clientSocket.receive(reinterpret_cast<char*>(&msgLen), sizeof(uint32_t));
    msgLen = ntohl(msgLen);
    buffer.clear();
    buffer.resize(msgLen);
    clientSocket.receive(buffer.data(), msgLen);
    msgpack::type::tuple<GameType::PlayerEvent> creationID;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(creationID);
    if (std::get<0>(creationID) == GameType::CREATE_PLAYER) {
        return _createPlayer(buffer, offset);
    } else if (std::get<0>(creationID) == GameType::LOAD_PLAYER) {
        //_loadPlayer();//todo aca chequeamos en el archivo indice si existe el nombre de ese player
        throw TPException("No existe ese player en el archivo"); //todo no tirar siempre exception xd
    } else {
        throw TPException("No me llego ni mensaje de creacion ni de carga de player!");
    }
}

PlayerData ClientAccepter::_createPlayer(std::vector<char>& buffer, std::size_t& offset) {
    msgpack::type::tuple<std::string, GameType::Race, GameType::Class> info;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(info);
    PlayerData playerData = {std::move(std::get<0>(info)),
                             std::get<1>(info), std::get<2>(info)};
    return playerData;
}
