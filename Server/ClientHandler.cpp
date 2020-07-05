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

ClientHandler::ClientHandler(Socket &&socket, ServerProtocol& _protocol, PlayerProxy&& _player) :
                        socket(std::move(socket)), protocol(_protocol), player(std::move(_player)) {
    eventProcessors = {{GameType::MOVE, &ClientHandler::_processMove},
                       {GameType::PLAYER_ATTACK, &ClientHandler::_processAttack},
                       {GameType::PLAYER_USE_ITEM, &ClientHandler::_processUseItem}};
}

void ClientHandler::run() {
    try {
        uint32_t msgLength = 0;

        while (!finished) {
            buffer.clear();
            socket.receive((char*)&(msgLength), sizeof(uint32_t));
            msgLength = ntohl(msgLength);
            buffer.resize(msgLength);
            socket.receive(buffer.data(), msgLength);
            _processClientAction(buffer);
        }

    } catch(std::exception& e) {
        finished = true;
        std::cerr << e.what() << std::endl;
    }
}

void ClientHandler::sendGameUpdate() {
    try {
        const std::vector<char>& generalData = protocol.getGeneralData();
        if (generalData.size() != sizeof(uint32_t)) {
            socket.send(generalData.data(), generalData.size());
        }
        std::vector<char> playerData = ServerProtocol::getPlayerData(player);
        socket.send(playerData.data(), playerData.size());
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

bool ClientHandler::hasFinished() const {
    return finished;
}

void ClientHandler::update() {
    std::unique_lock<std::mutex> lk(m);
    player.giveEventsToGame();
}

void ClientHandler::sendCurrentGameState(const std::vector<char>& gameState) {
    try {
        const std::vector<char>& mapInfo = protocol.getMapInfo();
        socket.send(mapInfo.data(), mapInfo.size());
        socket.send(gameState.data(), gameState.size());
        std::vector<char> playerData = ServerProtocol::getPlayerData(player);
        socket.send(playerData.data(), playerData.size());
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

///////////////////////////////PRIVATE///////////////////////////////


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

void ClientHandler::_processClientAction(std::vector<char>& data) {
    offset = 0;
    msgpack::type::tuple<GameType::PlayerEvent> event;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(event);
    (this->*eventProcessors.at(std::get<0>(event)))(data);
}

void ClientHandler::_processMove(std::vector<char> &data) {
    msgpack::type::tuple<GameType::Direction> moveInfo;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(moveInfo);
    player.move(std::get<0>(moveInfo));
}

void ClientHandler::_processAttack(std::vector<char> &data) {
    msgpack::type::tuple<int32_t, int32_t> attackInfo;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(attackInfo);
    player.attack({std::get<0>(attackInfo), std::get<1>(attackInfo)});
}

void ClientHandler::_processUseItem(std::vector<char> &data) {
    msgpack::type::tuple<int32_t> itemPosition;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(itemPosition);
    player.useItem(std::get<0>(itemPosition));
}

void ClientHandler::removePlayer() {
    player.remove();
}

void ClientHandler::forceFinish() {
    socket.close();
}
