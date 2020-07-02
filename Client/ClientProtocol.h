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
#include "../SDL/GUI/GUIPlayerInfo.h"

struct EntityData {
    TextureID texture;
    std::string nickname;
    Coordinate pos;
};

struct PlayerData {
    GUIPlayerInfo generalInfo;
    std::vector<std::tuple<TextureID, EquippedItems>> equippedItems;
    std::vector<std::tuple<TextureID, int>> inventoryItems;
};

struct MapPlayerData {
    EntityData entityData;
    GameType::Race race{};
    PlayerEquipment equipment{};
    bool isAlive{};
};

struct ItemData {
    Coordinate position;
    TextureID texture;
};

class Socket;

class ClientProtocol {
private:
    Socket& socket;
    ProtocolEnumTranslator translator;
    msgpack::object_handle handler;
    std::vector<char>* buffer;

public:
    explicit ClientProtocol(Socket& _socket) : socket(_socket) {}
    MapPlayerData processAddPlayer(std::vector<char>* _buffer, msgpack::type::tuple<GameType::Entity,
            std::string, int32_t, int32_t>& entityData, std::size_t& offset);
    EntityData processAddNPC(std::vector<char>* _buffer, msgpack::type::tuple<GameType::Entity,
            std::string, int32_t, int32_t> &entityData,
                              size_t &offset);
    ItemData processAddItem(std::vector<char>* _buffer, std::size_t& offset);
    PlayerData processAddPlayerData(size_t& offset);//Esta va a ir al protocol general
    static void loadBytes(std::vector<char> &loadBuffer, void *data, unsigned int size);


private:
    void _addManaData(PlayerData& data, size_t& offset);
    void _addHealthData(PlayerData& data, size_t& offset);
    void _addXPData(PlayerData& data, size_t& offset);
    void _addEquippedItems(PlayerData& info, size_t &offset);
    void _addClothing(PlayerData& info, size_t &offset, EquippedItems item);
    void _addWeapon(PlayerData& info, size_t &offset);
    void _fillInventory(PlayerData& info, size_t &offset);
    void _addItem(PlayerData& info, GameType::ItemType type, int32_t id, int position);
    void _addSkills(PlayerData& data, size_t &offset);
    void _addPosition(PlayerData& data, size_t &offset);
    void _addPlayerStats(PlayerData& data, size_t& offset);
    void _addInventoryItems(PlayerData& data, size_t& offset);
};


#endif //ARGENTUM_CLIENTPROTOCOL_H
