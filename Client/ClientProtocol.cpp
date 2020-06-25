//
// Created by ivan on 24/6/20.
//

#include "ClientProtocol.h"
#include "Socket.h"
#include <vector>
#include <msgpack.hpp>

#include <iostream>

void ClientProtocol::receiveMapInfo() {
    uint32_t msgLength;
    socket.receive((char*)(&msgLength), sizeof(msgLength));
    msgLength = ntohl(msgLength);
    std::vector<char> mapInfo(msgLength);
    socket.receive(mapInfo.data(), mapInfo.size());
    std::string str(mapInfo.begin(), mapInfo.end());
    std::size_t offset = 0;
    msgpack::object_handle oh = msgpack::unpack(str.data(), str.size(), offset);
    msgpack::type::tuple<int32_t, int32_t> mapSize;
    oh->convert(mapSize);
    int rows = std::get<0>(mapSize);
    int columns = std::get<1>(mapSize);
    game.setMapSize(rows, columns);
    for (int i = 0; i < rows*columns; ++i) {
        oh = msgpack::unpack(str.data(), str.size(), offset);
        msgpack::type::tuple<int32_t, int32_t> tileInfo;
    }
}

ClientProtocol::ClientProtocol(Socket &_socket) : socket(_socket) {
    _translateEntities();
    _translateFloorTypes();
    _translateStructures();
}

void ClientProtocol::_translateEntities(){
    entitiesMap.emplace(GameType::Entity::SKELETON, Skeleton);
    entitiesMap.emplace(GameType::Entity::ZOMBIE, Zombie);
    entitiesMap.emplace(GameType::Entity::SPIDER, Spider);
    entitiesMap.emplace(GameType::Entity::GOBLIN, Goblin);
    entitiesMap.emplace(GameType::Entity::BANKER, Banker);
    entitiesMap.emplace(GameType::Entity::GUARD, Guard);
    entitiesMap.emplace(GameType::Entity::TRADER, Trader);
    entitiesMap.emplace(GameType::Entity::PRIEST, Priest);
    entitiesMap.emplace(GameType::Entity::NOTHING, Nothing);
}

void ClientProtocol::_translateFloorTypes() {
    floorTypesMap.emplace(GameType::FloorType::GRASS0, Grass);
    floorTypesMap.emplace(GameType::FloorType::GRASS1, Grass);
    floorTypesMap.emplace(GameType::FloorType::GRASS2, Grass);
    floorTypesMap.emplace(GameType::FloorType::GRASS3, Grass);
    floorTypesMap.emplace(GameType::FloorType::SAND, Sand);
    floorTypesMap.emplace(GameType::FloorType::WATER0, Water);
    floorTypesMap.emplace(GameType::FloorType::WATER1, Water);
    floorTypesMap.emplace(GameType::FloorType::WATER2, Water);
    floorTypesMap.emplace(GameType::FloorType::WATER3, Water);
    floorTypesMap.emplace(GameType::FloorType::PRETTY_ROAD0, PrettyRoad);
    floorTypesMap.emplace(GameType::FloorType::PRETTY_ROAD1, PrettyRoad);
    floorTypesMap.emplace(GameType::FloorType::PRETTY_ROAD2, PrettyRoad);
    floorTypesMap.emplace(GameType::FloorType::PRETTY_ROAD3, PrettyRoad);
    floorTypesMap.emplace(GameType::FloorType::PRETTY_GRASS0, PrettyGrass);
    floorTypesMap.emplace(GameType::FloorType::PRETTY_GRASS1, PrettyGrass);
    floorTypesMap.emplace(GameType::FloorType::PRETTY_GRASS2, PrettyGrass);
    floorTypesMap.emplace(GameType::FloorType::PRETTY_GRASS3, PrettyGrass);
    floorTypesMap.emplace(GameType::FloorType::DEAD_GRASS0, DeadGrass);
    floorTypesMap.emplace(GameType::FloorType::DEAD_GRASS1, DeadGrass);
    floorTypesMap.emplace(GameType::FloorType::DEAD_GRASS2, DeadGrass);
    floorTypesMap.emplace(GameType::FloorType::DEAD_GRASS3, DeadGrass);
    floorTypesMap.emplace(GameType::FloorType::DARK_WATER0, DarkWater);
    floorTypesMap.emplace(GameType::FloorType::DARK_WATER1, DarkWater);
    floorTypesMap.emplace(GameType::FloorType::DARK_WATER2, DarkWater);
    floorTypesMap.emplace(GameType::FloorType::DARK_WATER3, DarkWater);
}

void ClientProtocol::_translateStructures() {
    structuresMap.emplace(GameType::Structure::BONE_GUY, BoneGuy);
    structuresMap.emplace(GameType::Structure::BROKEN_RIP_STONE, BrokenRipStone);
    structuresMap.emplace(GameType::Structure::BUSH, Bush);
    structuresMap.emplace(GameType::Structure::DEAD_BUSH, DeadBush);
    structuresMap.emplace(GameType::Structure::DEAD_GUY, DeadGuy);
    structuresMap.emplace(GameType::Structure::DEAD_TREE, DeadTree);
    structuresMap.emplace(GameType::Structure::FAT_TREE, FatTree);
    structuresMap.emplace(GameType::Structure::HANGED_GUY, HangedGuy);
    structuresMap.emplace(GameType::Structure::HOUSE1, House1);
    structuresMap.emplace(GameType::Structure::HOUSE2, House2);
    structuresMap.emplace(GameType::Structure::HOUSE3, House3);
    structuresMap.emplace(GameType::Structure::LONG_TREE, LongTree);
    structuresMap.emplace(GameType::Structure::PALM_TREE, PalmTree);
    structuresMap.emplace(GameType::Structure::RIP_STONE, RipStone);
    structuresMap.emplace(GameType::Structure::TREE, Tree);
    structuresMap.emplace(GameType::Structure::VERY_DEAD_GUY, VeryDeadGuy);
    structuresMap.emplace(GameType::Structure::SUNKEN_COLUMN, SunkenColumn);
    structuresMap.emplace(GameType::Structure::SUNKEN_SHIP, SunkenShip);
}
