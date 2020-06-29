//
// Created by ivan on 24/6/20.
//

#ifndef ARGENTUM_CLIENTPROTOCOL_H
#define ARGENTUM_CLIENTPROTOCOL_H

#include "../Shared/GameEnums.h"
#include <vector>
#include <msgpack.hpp>
#include "ProtocolEnumTranslator.h"

class GameGUI;
class Socket;

class ClientProtocol {
private:
    GameGUI& game;
    Socket& socket;
    std::vector<char> buffer;
    ProtocolEnumTranslator translator;

public:
    ClientProtocol(GameGUI& _game, Socket& _socket);

private:
    void _receiveMapInfo();
    void _loadMap();
    void _receiveCurrentGameState();
    //Meter handler y offset en la clase para no mandarlo siempre
    void _processAddEntity(msgpack::object_handle &handler, std::size_t& offset);
    void _processAddItem(msgpack::object_handle &handler, std::size_t& offset);
    void _processAddPlayer(msgpack::type::tuple<GameType::Entity,
            std::string, int32_t, int32_t>& entityData, msgpack::object_handle& handler,
            std::size_t& offset);
    void _processAddInventoryItems(msgpack::object_handle &handler, size_t& offset);
    void _processAddPlayerData(msgpack::object_handle &handler, size_t& offset);
    void _addManaData(msgpack::object_handle &handler, size_t& offset);
    void _addHealthData(msgpack::object_handle &handler, size_t& offset);
    void _addXPData(msgpack::object_handle &handler, size_t& offset);
    void _addEquippedItems(msgpack::object_handle &handler, size_t &offset);
    void _addClothing(msgpack::object_handle &handler, size_t &offset);
    void _addWeapon(msgpack::object_handle &handler, size_t &offset);
    void _fillInventory(msgpack::object_handle &handler, size_t &offset);
    void _addItem(msgpack::object_handle &handler, size_t &offset);
};


#endif //ARGENTUM_CLIENTPROTOCOL_H
