//
// Created by ivan on 24/6/20.
//

#ifndef ARGENTUM_CLIENTPROTOCOL_H
#define ARGENTUM_CLIENTPROTOCOL_H

#include "../SDL/GUI/PlayerInventoryGUI.h"//para el equippeditems enum
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
    //Meto estas dos cosas en la clase xq las mandabamos como parametros en el 90% de los metodos
    msgpack::object_handle handler;
    /*size_t offset{};*/

public:
    ClientProtocol(GameGUI& _game, Socket& _socket);

private://No se si todas las q estan aca son private
    void _receiveMapInfo();
    void _loadMap();
    void _receiveCurrentGameState();
    void _processAddEntity(std::size_t& offset);
    void _processAddItem(std::size_t& offset);
    void _processAddPlayer(msgpack::type::tuple<GameType::Entity,
            std::string, int32_t, int32_t>& entityData, std::size_t& offset);
    void _processAddInventoryItems(size_t& offset);
    void _processAddPlayerData(size_t& offset);
    void _addManaData(size_t& offset);
    void _addHealthData(size_t& offset);
    void _addXPData(size_t& offset);
    void _addEquippedItems(size_t &offset);
    void _addClothing(size_t &offset, EquippedItems item);
    void _addWeapon(size_t &offset);
    void _fillInventory(size_t &offset);
    void _addItem(GameType::ItemType type, int32_t id, int position);
    void _addSkills(size_t &offset);
    void _addPosition(size_t &offset);
};


#endif //ARGENTUM_CLIENTPROTOCOL_H
