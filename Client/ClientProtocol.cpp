//
// Created by ivan on 24/6/20.
//

#include "ClientProtocol.h"
#include "Socket.h"
#include <vector>
#include <msgpack.hpp>
#include "../Shared/GameEnums.h"

MSGPACK_ADD_ENUM(GameType::FloorType)
MSGPACK_ADD_ENUM(GameType::Structure)
MSGPACK_ADD_ENUM(GameType::Entity)

void ClientProtocol::receiveMapInfo() {
    uint32_t msgLength;
    socket.receive((char*)(&msgLength), sizeof(msgLength));
    msgLength = ntohl(msgLength);
    std::vector<char> mapInfo(msgLength);
    socket.receive(mapInfo.data(), mapInfo.size());
    std::string str(mapInfo.begin(), mapInfo.end());
    std::size_t offset = 0;
    msgpack::object_handle handler = msgpack::unpack(str.data(), str.size(), offset);
    msgpack::type::tuple<int32_t, int32_t> mapSize;
    handler->convert(mapSize);
    int rows = std::get<0>(mapSize);
    int columns = std::get<1>(mapSize);
    game.setMapSize(rows, columns);
    for (int i = 0; i < rows*columns; ++i) {
        handler = msgpack::unpack(str.data(), str.size(), offset);
        msgpack::type::tuple<GameType::FloorType, GameType::Structure, GameType::Entity> tileInfo;
        std::cout << handler.get() << std::endl;
        handler->convert(tileInfo);
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

void ClientProtocol::_translateRaces() {
    racesMap.emplace(GameType::Race::HUMAN, HumanHead);
    racesMap.emplace(GameType::Race::ELF, ElfHead);
    racesMap.emplace(GameType::Race::DWARF, DwarfHead);
    racesMap.emplace(GameType::Race::GNOME, GnomeHead);

}

void ClientProtocol::_translateWeapons() {
    weaponsMap.emplace(GameType::Weapon::LONGSWORD, LongSword);
    weaponsMap.emplace(GameType::Weapon::AXE, Axe);
    weaponsMap.emplace(GameType::Weapon::WARHAMMER, WarHammer);
    weaponsMap.emplace(GameType::Weapon::ASH_ROD, AshRod);
    weaponsMap.emplace(GameType::Weapon::ELVEN_FLUTE, ElvenFlute);
    weaponsMap.emplace(GameType::Weapon::LINKED_STAFF, LinkedStaff);
    weaponsMap.emplace(GameType::Weapon::SIMPLE_BOW, SimpleBow);
    weaponsMap.emplace(GameType::Weapon::COMPOSITE_BOW, CompositeBow);
    weaponsMap.emplace(GameType::Weapon::GNARLED_STAFF, GnarledStaff);
    weaponsMap.emplace(GameType::Weapon::FIST, Nothing);
}

void ClientProtocol::_translateWeaponDrops() {
    weaponDropsMap.emplace(GameType::Weapon::LONGSWORD, LongSwordDrop);
    weaponDropsMap.emplace(GameType::Weapon::AXE, AxeDrop);
    weaponDropsMap.emplace(GameType::Weapon::WARHAMMER, WarHammerDrop);
    weaponDropsMap.emplace(GameType::Weapon::ASH_ROD, AshRodDrop);
    weaponDropsMap.emplace(GameType::Weapon::ELVEN_FLUTE, ElvenFluteDrop);
    weaponDropsMap.emplace(GameType::Weapon::LINKED_STAFF, LinkedStaffDrop);
    weaponDropsMap.emplace(GameType::Weapon::SIMPLE_BOW, SimpleBowDrop);
    weaponDropsMap.emplace(GameType::Weapon::COMPOSITE_BOW, CompositeBowDrop);
    weaponDropsMap.emplace(GameType::Weapon::GNARLED_STAFF, GnarledStaffDrop);
    weaponDropsMap.emplace(GameType::Weapon::FIST, Nothing);
}

void ClientProtocol::_translateClothing() {
    clothingMap.emplace(GameType::Clothing::COMMON_CLOTHING, CommonClothing);
    clothingMap.emplace(GameType::Clothing::LEATHER_ARMOR, LeatherArmor);
    clothingMap.emplace(GameType::Clothing::PLATE_ARMOR, PlateArmor);
    clothingMap.emplace(GameType::Clothing::BLUE_TUNIC, BlueTunic);
    clothingMap.emplace(GameType::Clothing::HOOD, Hood);
    clothingMap.emplace(GameType::Clothing::IRON_HELMET, IronHelmet);
    clothingMap.emplace(GameType::Clothing::TURTLE_SHIELD, TurtleShield);
    clothingMap.emplace(GameType::Clothing::IRON_SHIELD, IronShield);
    clothingMap.emplace(GameType::Clothing::MAGIC_HAT, MagicHat);
    clothingMap.emplace(GameType::Clothing::NO_HELMET, Nothing);
    clothingMap.emplace(GameType::Clothing::NO_SHIELD, Nothing);
}

void ClientProtocol::_translateClothingDrops() {
    clothingDropsMap.emplace(GameType::Clothing::COMMON_CLOTHING,CommonClothingDrop);
    clothingDropsMap.emplace(GameType::Clothing::LEATHER_ARMOR, LeatherArmorDrop);
    clothingDropsMap.emplace(GameType::Clothing::PLATE_ARMOR, PlateArmorDrop);
    clothingDropsMap.emplace(GameType::Clothing::BLUE_TUNIC, BlueTunicDrop);
    clothingDropsMap.emplace(GameType::Clothing::HOOD, HoodDrop);
    clothingDropsMap.emplace(GameType::Clothing::IRON_HELMET, IronHelmetDrop);
    clothingDropsMap.emplace(GameType::Clothing::TURTLE_SHIELD, TurtleShieldDrop);
    clothingDropsMap.emplace(GameType::Clothing::IRON_SHIELD, IronShieldDrop);
    clothingDropsMap.emplace(GameType::Clothing::MAGIC_HAT, MagicHatDrop);
    clothingDropsMap.emplace(GameType::Clothing::NO_HELMET, Nothing);
    clothingDropsMap.emplace(GameType::Clothing::NO_SHIELD, Nothing);
}

void ClientProtocol::_translatePotions() {
    potionsMap.emplace(GameType::Potion::HEALTH_POTION, HealthPotion);
    potionsMap.emplace(GameType::Potion::MANA_POTION, ManaPotion);
}
