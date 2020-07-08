#include "ClientHandler.h"
#include <vector>
#include <mutex>
#include "ServerProtocol.h"
#include "PlayerLoader.h"
#include <iostream>
#include "../TPException.h"
#include <iostream>

MSGPACK_ADD_ENUM(GameType::PlayerEvent)
MSGPACK_ADD_ENUM(GameType::Race)
MSGPACK_ADD_ENUM(GameType::Class)
MSGPACK_ADD_ENUM(GameType::Direction)
MSGPACK_ADD_ENUM(GameType::EquipmentPlace)

///////////////////////////////PUBLIC///////////////////////////////

ClientHandler::ClientHandler(Socket &&socket, ServerProtocol& _protocol) :
                        socket(std::move(socket)), protocol(_protocol) {
    eventProcessors = {{GameType::MOVE, &ClientHandler::_processMove},
                       {GameType::PLAYER_ATTACK, &ClientHandler::_processAttack},
                       {GameType::PLAYER_USE_ITEM, &ClientHandler::_processUseItem},
                       {GameType::PLAYER_UNEQUIP, &ClientHandler::_processUnequip},
                       {GameType::PLAYER_PICK_UP, &ClientHandler::_processPickUp},
                       {GameType::PLAYER_DROP, &ClientHandler::_processDrop},
                       {GameType::PLAYER_LIST, &ClientHandler::_processList},
                       {GameType::PLAYER_BUY, &ClientHandler::_processBuy},
                       {GameType::PLAYER_SELL, &ClientHandler::_processSell},
                       {GameType::PLAYER_WITHDRAW, &ClientHandler::_processWithdraw},
                       {GameType::PLAYER_DEPOSIT, &ClientHandler::_processDeposit}};


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
        socket.close();
        finished = true;
        std::cerr << e.what() << std::endl;
    }
}

void ClientHandler::sendGameUpdate() {
    try {
        const std::vector<char>& generalData = protocol.getGeneralData();
        socket.send(generalData.data(), generalData.size());
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


void ClientHandler::removePlayer() {
    player.remove(protocol);
}

void ClientHandler::forceFinish() {
    socket.close();
}

void ClientHandler::setPlayerProxy(PlayerProxy&& _player) {
    player = std::move(_player);
}


///////////////////////////////PRIVATE///////////////////////////////


void ClientHandler::_processClientAction(std::vector<char>& data) {
    offset = 0;
    msgpack::type::tuple<GameType::PlayerEvent> event;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(event);
    std::unique_lock<std::mutex> lk(m);
    try {
        (this->*eventProcessors.at(std::get<0>(event)))(data);
    } catch(std::out_of_range& e) {
        std::cerr << "Se recibio un comando desconocido" << std::endl;
    }
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

void ClientHandler::_processUnequip(std::vector<char> &data) {
    msgpack::type::tuple<GameType::EquipmentPlace> equipmentPlace;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(equipmentPlace);
    player.unequip(std::get<0>(equipmentPlace));
}

void ClientHandler::_processPickUp(std::vector<char> &data) {
    player.pickUpItem();
}

void ClientHandler::_processDrop(std::vector<char> &data) {
    msgpack::type::tuple<int32_t> itemPosition;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(itemPosition);
    player.dropItem(std::get<0>(itemPosition));
}

void ClientHandler::_processList(std::vector<char> &data) {
    msgpack::type::tuple<int32_t, int32_t> listPosition;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(listPosition);
    player.listFrom({std::get<0>(listPosition), std::get<1>(listPosition)});
}

void ClientHandler::_processBuy(std::vector<char> &data) {
    msgpack::type::tuple<std::string, int32_t, int32_t> buyArguments;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(buyArguments);
    player.buyFrom(std::move(std::get<0>(buyArguments)),
                   {std::get<1>(buyArguments), std::get<2>(buyArguments)});
}

void ClientHandler::_processSell(std::vector<char> &data) {
    msgpack::type::tuple<std::string, int32_t, int32_t> sellArguments;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(sellArguments);
    player.sellTo(std::move(std::get<0>(sellArguments)),
                   {std::get<1>(sellArguments), std::get<2>(sellArguments)});
}

void ClientHandler::_processWithdraw(std::vector<char> &data) {
    msgpack::type::tuple<std::string, int32_t, int32_t> sellArguments;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(sellArguments);
    player.withdrawFrom(std::move(std::get<0>(sellArguments)),
                  {std::get<1>(sellArguments), std::get<2>(sellArguments)});
}

void ClientHandler::_processDeposit(std::vector<char> &data) {
    msgpack::type::tuple<std::string, int32_t, int32_t> depositArguments;
    handler = msgpack::unpack(data.data(), data.size(), offset);
    handler->convert(depositArguments);
    player.depositTo(std::move(std::get<0>(depositArguments)),
                        {std::get<1>(depositArguments), std::get<2>(depositArguments)});
}
