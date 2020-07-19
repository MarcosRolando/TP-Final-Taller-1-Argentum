//
// Created by marcos on 6/24/20.
//

#include "ClientAccepter.h"
#include "../../libs/Socket.h"
#include "ClientHandler.h"
#include "ClientsMonitor.h"
#include <iostream>
#include "PlayerManager.h"
#include "../Exceptions/UnavailablePlayerException.h"
#include "../Exceptions/InexistentPlayerException.h"

MSGPACK_ADD_ENUM(GameType::PlayerEvent)
MSGPACK_ADD_ENUM(GameType::Class)
MSGPACK_ADD_ENUM(GameType::Race)

void ClientAccepter::_acceptClients() {
    GameType::ConnectionResponse status;
    while (keepRunning) {
        Socket clientSocket = serverSocket.accept();
        try {
            PlayerData playerData = _receivePlayerInfo(clientSocket);
            status = GameType::ACCEPTED;
            if (_sendResponseToClient(clientSocket, status)) {
                clients.pushToWaitingList(std::move(clientSocket), protocol, std::move(playerData));
            }
        } catch(InexistentPlayerException& e) {
            status = GameType::INEXISTENT_PLAYER;
            _sendResponseToClient(clientSocket, status);
        } catch (UnavailablePlayerException& e) {
            status = GameType::UNAVAILABLE_PLAYER;
            _sendResponseToClient(clientSocket, status);
        } catch(std::exception& e) {
            std::cerr << e.what() << " in accepter" << std::endl;
            status = GameType::UNKOWN_SERVER_ERROR;
            _sendResponseToClient(clientSocket, status);
        } catch(...) {
            std::cerr << "Uknown error while reading a client player information in accepter!" << std::endl;
            status = GameType::UNKOWN_SERVER_ERROR;
            _sendResponseToClient(clientSocket, status);
        }
    }
}

bool ClientAccepter::_sendResponseToClient(Socket& clientSocket, GameType::ConnectionResponse status) {
    status = static_cast<GameType::ConnectionResponse>(htonl(status));
    try {
        clientSocket.send(reinterpret_cast<char*>(&status), sizeof(status));
    } catch(...) {
        std::cerr << "Client disconnected suddenly in accepter" << std::endl;
        return false;
    }
    return true;
}

void ClientAccepter::run() {
    try {
        _acceptClients();
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
        throw TPException("Invalidad load/create client messages!");
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
