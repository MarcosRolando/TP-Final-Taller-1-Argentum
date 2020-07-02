//
// Created by ivan on 24/6/20.
//

#include "ClientProtocol.h"
#include "GameGUI.h"
#include "Socket.h"

MSGPACK_ADD_ENUM(GameType::EventID)
MSGPACK_ADD_ENUM(GameType::Race)
MSGPACK_ADD_ENUM(GameType::FloorType)
MSGPACK_ADD_ENUM(GameType::Structure)
MSGPACK_ADD_ENUM(GameType::Entity)
MSGPACK_ADD_ENUM(GameType::Weapon)
MSGPACK_ADD_ENUM(GameType::Clothing)
MSGPACK_ADD_ENUM(GameType::Potion)
MSGPACK_ADD_ENUM(GameType::ItemType)
MSGPACK_ADD_ENUM(GameType::Class)
MSGPACK_ADD_ENUM(GameType::PlayerEvent)
MSGPACK_ADD_ENUM(GameType::Direction)


//La copie de ClientEventHandler pero creo q va mejor aca
void ClientProtocol::loadBytes(std::vector<char>& loadBuffer, void* data, unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        loadBuffer[i] = *(reinterpret_cast<char *>(data) + i);
    }
}

ItemData ClientProtocol::processAddItem(std::vector<char>* _buffer, std::size_t& offset) {

    buffer = _buffer;
    TextureID itemTexture = Nothing;
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
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
    return {{std::get<2>(itemData), std::get<3>(itemData)}, itemTexture};
}

EntityData ClientProtocol::processAddNPC(std::vector<char>* _buffer, msgpack::type::tuple<GameType::Entity,
        std::string>& entityData, std::size_t& offset) {

    buffer = _buffer;
    EntityData npcData;
    npcData.texture = translator.getEntityTexture(std::get<0>(entityData));
    npcData.nickname = std::get<1>(entityData);
    msgpack::type::tuple<int32_t, int32_t, GameType::Direction, int32_t> position;
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    handler->convert(position);
    npcData.pos = {std::get<0>(position), std::get<1>(position)};
    npcData.currentDir = static_cast<GameType::Direction>(std::get<2>(position));
    npcData.distanceMoved = std::get<3>(position);
    return npcData;
}

MapPlayerData ClientProtocol::processAddPlayer(std::vector<char>* _buffer, msgpack::type::tuple<GameType::Entity,
        std::string>& entityData, std::size_t& offset) {

    buffer = _buffer;
    MapPlayerData pData;
    PlayerEquipment equipment{};
    pData.entityData.texture = Nothing; /*no lo usamos para nada despues igual*/
    pData.entityData.nickname = std::get<1>(entityData);
    msgpack::type::tuple<int32_t, int32_t, GameType::Direction, int32_t> position;
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    handler->convert(position);
    pData.entityData.pos = {std::get<0>(position), std::get<1>(position)};
    pData.entityData.currentDir = std::get<2>(position);
    pData.entityData.distanceMoved = std::get<3>(position);
    msgpack::type::tuple<GameType::Race> playerRace;
    msgpack::type::tuple<int32_t> item;
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    handler->convert(playerRace);
    msgpack::type::tuple<bool> isAlive;
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    handler->convert(isAlive);
    equipment.head = translator.getRaceTexture(
            static_cast<GameType::Race>(std::get<0>(playerRace))); //todo ver si hago funcion privada para la ropa
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    handler->convert(item); /*Recibo en orden el helmet, armor, shield y weapon*/
    equipment.helmet = translator.getClothingTexture(
            static_cast<GameType::Clothing>(std::get<0>(item)));
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    handler->convert(item);
    equipment.body = translator.getClothingTexture(
            static_cast<GameType::Clothing>(std::get<0>(item)));
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    handler->convert(item);
    equipment.shield = translator.getClothingTexture(
            static_cast<GameType::Clothing>(std::get<0>(item)));
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    handler->convert(item);
    equipment.weapon = translator.getWeaponTexture(
            static_cast<GameType::Weapon>(std::get<0>(item)));

    pData.equipment = equipment;
    pData.isAlive = std::get<0>(isAlive);
    pData.race = std::get<0>(playerRace);
    return pData;
}

void ClientProtocol::_addInventoryItems(PlayerData& data, size_t& offset) {
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    msgpack::type::tuple<int32_t> gold;
    handler->convert(gold);
    data.generalInfo.gold = std::get<0>(gold);
    //Aca recibe los items del inventario
    _addEquippedItems(data, offset);
    _fillInventory(data, offset);
}

void ClientProtocol::_addEquippedItems(PlayerData& info, size_t& offset){
    _addClothing(info, offset, Helmet);//Esto carga el helmet
    _addClothing(info, offset, Armor);//Esto carga la armadura
    _addClothing(info, offset, Shield);//Esto carga el shield
    _addWeapon(info, offset);
}

void ClientProtocol::_fillInventory(PlayerData& info, size_t& offset){
    for (int i = 0; i < 16; ++i) {
        handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
        msgpack::type::tuple<GameType::ItemType, int32_t> item;
        handler->convert(item);
        if (static_cast<GameType::ItemType>(std::get<0>(item)) != GameType::ITEM_TYPE_NONE) {
            _addItem(info, std::get<0>(item), std::get<1>(item), i);
        }
    }
}

void ClientProtocol::_addItem(PlayerData& info, GameType::ItemType type, int32_t id, int position) {
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
    info.inventoryItems.emplace_back(texture, position);
}

void ClientProtocol::_addPlayerStats(PlayerData& data, size_t& offset) {
    _addXPData(data, offset);
    _addManaData(data, offset);
    _addHealthData(data, offset);
    _addSkills(data, offset);
    _addPosition(data, offset);
}

void ClientProtocol::_addClothing(PlayerData& info, size_t& offset, EquippedItems item) {
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    msgpack::type::tuple<int32_t> equippedClothing;
    handler->convert(equippedClothing);
    info.equippedItems.emplace_back(translator.getClothingDropTexture
            (static_cast<GameType::Clothing>(std::get<0>(equippedClothing))), item);
}

void ClientProtocol::_addWeapon(PlayerData& info, size_t& offset){
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    msgpack::type::tuple<int32_t> equippedWeapon;
    handler->convert(equippedWeapon);
    info.equippedItems.emplace_back(translator.getWeaponTexture(
            static_cast<GameType::Weapon>(std::get<0>(equippedWeapon))), Weapon);
}

void ClientProtocol::_addXPData(PlayerData& data, size_t& offset) {
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    msgpack::type::tuple<int32_t, int32_t, int32_t> xpData;
    handler->convert(xpData);
    data.generalInfo.xp = std::get<0>(xpData);
    data.generalInfo.nextLevelXP = std::get<1>(xpData);
    data.generalInfo.level = std::get<2>(xpData);
}

void ClientProtocol::_addHealthData(PlayerData& data, size_t& offset) {
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    msgpack::type::tuple<int32_t, int32_t> healthData;
    handler->convert(healthData);
    data.generalInfo.health = std::get<0>(healthData);
    data.generalInfo.totalHealth = std::get<1>(healthData);
}

void ClientProtocol::_addManaData(PlayerData& data, size_t& offset) {
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    msgpack::type::tuple<int32_t, int32_t> manaData;
    handler->convert(manaData);
    data.generalInfo.mana = std::get<0>(manaData);
    data.generalInfo.totalMana = std::get<1>(manaData);
}

void ClientProtocol::_addSkills(PlayerData& data, size_t& offset){
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    msgpack::type::tuple<int32_t, int32_t, int32_t, int32_t> skills;
    handler->convert(skills);
    data.generalInfo.strength = std::get<0>(skills);
    data.generalInfo.constitution = std::get<1>(skills);
    data.generalInfo.intelligence = std::get<2>(skills);
    data.generalInfo.agility = std::get<3>(skills);
}

void ClientProtocol::_addPosition(PlayerData& data, size_t& offset) {
    handler = msgpack::unpack(buffer->data(), buffer->size(), offset);
    msgpack::type::tuple<int32_t, int32_t> pos;
    handler->convert(pos);
    data.generalInfo.position = {std::get<1>(pos), std::get<0>(pos)};
}

PlayerData ClientProtocol::processAddPlayerData() {
    std::size_t offset = 0;
    PlayerData data;
    _addInventoryItems(data, offset);
    _addPlayerStats(data, offset);
    return data;
}
