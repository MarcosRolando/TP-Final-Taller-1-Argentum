//
// Created by ivan on 24/6/20.
//

#ifndef ARGENTUM_CLIENTPROTOCOL_H
#define ARGENTUM_CLIENTPROTOCOL_H

#include "../Graphics/GUI/PlayerInventoryGUI.h"//para el equippeditems enum
#include "../../libs/GameEnums.h"
#include <vector>
#include <msgpack.hpp>
#include "ProtocolEnumTranslator.h"
#include "../Texture/PlayerEquipment.h"
#include "../Map/Coordinate.h"
#include "../Graphics/GUI/GUIPlayerInfo.h"
#include "EntityData.h"

class Socket;

class ClientProtocol {
private:
    Socket& socket;
    ProtocolEnumTranslator translator;
    msgpack::object_handle handler;
    std::vector<char>* buffer{};

public:
    explicit ClientProtocol(Socket& _socket) : socket(_socket) {}
    MapPlayerData processAddPlayer(std::vector<char>* _buffer, msgpack::type::tuple<GameType::Entity,
            std::string>& entityData, std::size_t& offset);
    EntityData processAddNPC(std::vector<char>* _buffer, msgpack::type::tuple<GameType::Entity,
            std::string> &entityData,
                              size_t &offset);
    ItemData processAddItem(std::vector<char>* _buffer, std::size_t& offset);
    PlayerData processAddPlayerData(std::vector<char>* _buffer);
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

    void _addMinichatText(PlayerData &data, size_t &offset);

    void _addNickname(PlayerData &data, size_t &offset);
};


#endif //ARGENTUM_CLIENTPROTOCOL_H
