//
// Created by ivan on 24/6/20.
//

#include "ClientProtocol.h"
#include "GameGUI.h"
#include "Socket.h"
#include "../Shared/GameEnums.h"
#include "../Texture/PlayerEquipment.h"

MSGPACK_ADD_ENUM(GameType::ID)
MSGPACK_ADD_ENUM(GameType::Race)
MSGPACK_ADD_ENUM(GameType::FloorType)
MSGPACK_ADD_ENUM(GameType::Structure)
MSGPACK_ADD_ENUM(GameType::Entity)
MSGPACK_ADD_ENUM(GameType::Weapon)
MSGPACK_ADD_ENUM(GameType::Clothing)
MSGPACK_ADD_ENUM(GameType::Potion)
MSGPACK_ADD_ENUM(GameType::ItemType)

ClientProtocol::ClientProtocol(GameGUI &_game, Socket &_socket) : game(_game), socket(_socket) {
    _receiveMapInfo();
    _receiveCurrentGameState();
}

void ClientProtocol::_receiveMapInfo() {
    int32_t msgLength;
    socket.receive((char*)(&msgLength), sizeof(msgLength));
    msgLength = ntohl(msgLength);
    buffer.resize(msgLength);
    socket.receive(buffer.data(), buffer.size());
    _loadMap();
}

void ClientProtocol::_loadMap() {
    std::size_t offset = 0;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<int32_t, int32_t> mapSize;
    handler->convert(mapSize);
    int rows = std::get<0>(mapSize);
    int columns = std::get<1>(mapSize);
    game.setMapSize(rows, columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
            msgpack::type::tuple<GameType::FloorType, GameType::Structure, GameType::Entity> tileInfo;
            handler->convert(tileInfo);
            game.loadTileData({i, j}, translator.getFloorTypeTexture(std::get<0>(tileInfo)),
                              translator.getStructureTexture(std::get<1>(tileInfo)),
                              translator.getEntityTexture(std::get<2>(tileInfo)));
        }
    }
}


void ClientProtocol::_receiveCurrentGameState() {
    int32_t msgLength;
    socket.receive((char*)(&msgLength), sizeof(msgLength));
    msgLength = ntohl(msgLength);
    buffer.resize(msgLength);
    socket.receive(buffer.data(), msgLength);
    std::size_t offset = 0;

    while (offset < static_cast<size_t>(msgLength)) {
        handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
        msgpack::type::tuple<GameType::ID> id;
        handler->convert(id);
        if (std::get<0>(id) == GameType::ITEM) {
            _processAddItem(offset);
        } else if (std::get<0>(id) == GameType::ENTITY) {
            _processAddEntity(offset);
        } else if (std::get<0>(id) == GameType::PLAYER_DATA) {
            _processAddInventoryItems(offset);//Capaz me conviene poner esto
            //en una funcion para poder llamarla dsps en cada update
            _processAddPlayerData(offset);
        }
    }
}

void ClientProtocol::_processAddItem(std::size_t& offset) {
    TextureID itemTexture = Nothing;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<GameType::ItemType, int32_t, int32_t , int32_t> itemData;
    handler->convert(itemData);
    GameType::ItemType itemType = std::get<0>(itemData);

    if (itemType == GameType::ITEM_TYPE_WEAPON) {
        itemTexture = translator.getWeaponDropTexture(
                static_cast<GameType::Weapon>(std::get<1>(itemData)));

    } else if (itemType == GameType::ITEM_TYPE_CLOTHING) {
        itemTexture = translator.getClothingDropTexture(
                static_cast<GameType::Clothing>(std::get<1>(itemData)));

    } else if (itemType == GameType::ITEM_TYPE_POTION) {
        itemTexture = translator.getPotionTexture(
                static_cast<GameType::Potion>(std::get<1>(itemData)));
    }
    if (itemTexture != Nothing) {
        game.loadTileItem({std::get<2>(itemData), std::get<3>(itemData)}, itemTexture);
    }
}

void ClientProtocol::_processAddEntity(std::size_t& offset) {
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<GameType::Entity, std::string, int32_t , int32_t> entityData;
    handler->convert(entityData);
    if (std::get<0>(entityData) != GameType::PLAYER) {
        game.addNPC(translator.getEntityTexture(std::get<0>(entityData)),
                    std::move(std::get<1>(entityData)), {std::get<2>(entityData),
                                                         std::get<3>(entityData)});
    } else {
        _processAddPlayer(entityData,offset);
    }
}

void ClientProtocol::_processAddPlayer(msgpack::type::tuple<GameType::Entity,
        std::string, int32_t , int32_t>& entityData, std::size_t& offset) {

    PlayerEquipment equipment{};
    std::string nickname = std::get<1>(entityData);
    Coordinate position = {std::get<2>(entityData), std::get<3>(entityData)};
    msgpack::type::tuple<GameType::Race> playerRace;
    msgpack::type::tuple<int32_t> item;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(playerRace);
    msgpack::type::tuple<bool> isAlive;
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(isAlive);
    equipment.head = translator.getRaceTexture(
            static_cast<GameType::Race>(std::get<0>(playerRace))); //todo ver si hago funcion privada para la ropa
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(item); /*Recibo en orden el helmet, armor, shield y weapon*/
    equipment.helmet = translator.getClothingTexture(
            static_cast<GameType::Clothing>(std::get<0>(item)));
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(item);
    equipment.body = translator.getClothingTexture(
            static_cast<GameType::Clothing>(std::get<0>(item)));
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(item);
    equipment.shield = translator.getClothingTexture(
            static_cast<GameType::Clothing>(std::get<0>(item)));
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    handler->convert(item);
    equipment.weapon = translator.getWeaponTexture(
            static_cast<GameType::Weapon>(std::get<0>(item)));

    game.addPlayer(equipment, std::get<0>(isAlive), std::move(nickname), position);
}

void ClientProtocol::_processAddInventoryItems(size_t& offset) {
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<int32_t> gold;
    handler->convert(gold);
    game.getPlayerInventory().updateGold(std::get<0>(gold));
    //Aca recibe los items del inventario
    _addEquippedItems(offset);
    _fillInventory(offset);
}

void ClientProtocol::_addEquippedItems(size_t& offset){
    _addClothing(offset, Helmet);//Esto carga el helmet
    _addClothing(offset, Armor);//Esto carga la armadura
    _addClothing(offset, Shield);//Esto carga el shield
    _addWeapon(offset);
}

void ClientProtocol::_fillInventory(size_t& offset){
    for (int i = 0; i < 16; ++i) {
        handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
        msgpack::type::tuple<GameType::ItemType, int32_t> item;
        handler->convert(item);
        if (static_cast<GameType::ItemType>(std::get<0>(item)) != GameType::ITEM_TYPE_NONE){
            _addItem(std::get<0>(item), std::get<1>(item), i);
        }
    }
}

void ClientProtocol::_addItem(GameType::ItemType type, int32_t id, int position){
    TextureID texture;
    switch (type) {
        case GameType::ITEM_TYPE_WEAPON:
            texture = translator.getWeaponDropTexture(static_cast<GameType::Weapon>
                                                      (id));
            break;
        case GameType::ITEM_TYPE_CLOTHING:
            texture = translator.getClothingDropTexture(static_cast<GameType::Clothing>
                                                        (id));
            break;
        case GameType::ITEM_TYPE_POTION:
            texture = translator.getPotionTexture(static_cast<GameType::Potion>
                                                  (id));
            break;
        default:
            break;
    }
    game.getPlayerInventory().addInventoryItem(texture, position);
}

void ClientProtocol::_processAddPlayerData(size_t& offset) {
    _addXPData(offset);
    _addManaData(offset);
    _addHealthData(offset);
    _addSkills(offset);
    _addPosition(offset);
}

void ClientProtocol::_addClothing(size_t& offset, EquippedItems item){
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<int32_t> equippedClothing;
    handler->convert(equippedClothing);
    game.getPlayerInventory().addEquipableItem(translator.getClothingDropTexture
    (static_cast<GameType::Clothing>(std::get<0>(equippedClothing))), item);
}

void ClientProtocol::_addWeapon(size_t& offset){
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<int32_t> equippedWeapon;
    handler->convert(equippedWeapon);
    game.getPlayerInventory().addEquipableItem(translator.getWeaponDropTexture
    (static_cast<GameType::Weapon>(std::get<0>(equippedWeapon))),Weapon);
}

void ClientProtocol::_addXPData(size_t& offset) {
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<int32_t, int32_t, int32_t> xpData;
    handler->convert(xpData);
    game.getPlayerInfo().updateXP(std::get<0>(xpData));
    game.getPlayerInfo().updateNextLevelXP(std::get<1>(xpData));
    game.getPlayerInfo().updateLevel(std::get<2>(xpData));
}

void ClientProtocol::_addHealthData(size_t& offset) {
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<int32_t, int32_t> healthData;
    handler->convert(healthData);
    game.getPlayerInfo().updateHealth(std::get<0>(healthData));
    game.getPlayerInfo().updateTotalHealth(std::get<1>(healthData));
}

void ClientProtocol::_addManaData(size_t& offset) {
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<int32_t, int32_t> manaData;
    handler->convert(manaData);
    game.getPlayerInfo().updateMana(std::get<0>(manaData));
    game.getPlayerInfo().updateTotalMana(std::get<1>(manaData));
}

void ClientProtocol::_addSkills(size_t& offset){
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<int32_t, int32_t, int32_t, int32_t> skills;
    handler->convert(skills);
    game.getPlayerInfo().updateStrength(std::get<0>(skills));
    game.getPlayerInfo().updateConstitution(std::get<1>(skills));
    game.getPlayerInfo().updateIntelligence(std::get<2>(skills));
    game.getPlayerInfo().updateAgility(std::get<3>(skills));
}

void ClientProtocol::_addPosition(size_t& offset) {
    handler = msgpack::unpack(buffer.data(), buffer.size(), offset);
    msgpack::type::tuple<int32_t, int32_t> pos;
    handler->convert(pos);
    game.getPlayerInfo().updatePosition(std::get<1>(pos), std::get<0>(pos));
}
