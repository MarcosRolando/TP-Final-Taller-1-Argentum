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
#include "../Texture/PlayerEquipment.h"
#include "../Map/Coordinate.h"

struct EntityData {
    GameType::Entity type;
    std::string nickname;
    Coordinate pos;
};

struct PlayerData {
    EntityData entityData;
    GameType::Race race;
    PlayerEquipment equipment{};
    bool isAlive;
};
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
    void getInitialGameState();
    void createPlayer(const std::string &nickname, GameType::Race race,
                      GameType::Class _class);
    void loadPlayer(std::string &nickname);
    void _processAddEntity(std::size_t& offset);
    PlayerData _processAddPlayer(msgpack::type::tuple<GameType::Entity,
            std::string, int32_t, int32_t>& entityData, std::size_t& offset);
    EntityData _processAddNPC(msgpack::type::tuple<GameType::Entity, std::string, int32_t, int32_t> &entityData,
                              size_t &offset);


private:
    void _receiveMapInfo();
    void _loadMap();
    void _receiveCurrentGameState();
    void _processAddItem(std::size_t& offset);//Esta va a ir al protocol general
    void _processAddInventoryItems(size_t& offset);
    void _processAddPlayerData(size_t& offset);//Esta va a ir al protocol general
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
    void _loadBytes(std::vector<char> &loadBuffer, void *data, unsigned int size);
};


#endif //ARGENTUM_CLIENTPROTOCOL_H
