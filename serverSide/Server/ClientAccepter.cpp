//
// Created by marcos on 6/24/20.
//

#include "ClientAccepter.h"
#include "../../libs/Socket.h"
#include "ClientHandler.h"
#include "ClientsMonitor.h"
#include <iostream>
#include "../../libs/TPException.h"
#include "PlayerManager.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)
MSGPACK_ADD_ENUM(GameType::Class)
MSGPACK_ADD_ENUM(GameType::Race)

void ClientAccepter::run() {
    const char acceptedConnection = 1;
    const char deniedConnection = 0;
    try {
        while (keepRunning) {
            Socket clientSocket = serverSocket.accept();
            try {
                PlayerData playerData = _receivePlayerInfo(clientSocket);
                clientSocket.send(&acceptedConnection, sizeof(acceptedConnection));
                clients.pushToWaitingList(std::move(clientSocket), protocol, std::move(playerData));
            } catch(std::exception& e) {
                std::cerr << e.what() << std::endl;
                try {
                    clientSocket.send(&deniedConnection, sizeof(deniedConnection));
                } catch(...) {
                    //do nothing
                }
            }
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << " in accepter socket" << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in accepter socket" << std::endl;
    }
    keepRunning = false;
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
        return _loadPlayer(buffer, offset);
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
    manager.storeNewPlayer(playerData);
    return playerData;
}

PlayerData ClientAccepter::_loadPlayer(std::vector<char>& buffer, std::size_t& offset) {
    msgpack::type::tuple<std::string> nickname;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(nickname);
    return manager.getSavedPlayerData(std::get<0>(nickname));
}
