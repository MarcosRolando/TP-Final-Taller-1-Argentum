//
// Created by ivan on 25/6/20.
//

#include "ProtocolEnumTranslator.h"

ProtocolEnumTranslator::ProtocolEnumTranslator() {
    _translateEntities();
    _translateFloorTypes();
    _translateStructures();
    _translateRaces();
    _translateWeapons();
    _translateWeaponDrops();
    _translateClothing();
    _translateClothingDrops();
    _translatePotions();
}

void ProtocolEnumTranslator::_translateEntities(){
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

void ProtocolEnumTranslator::_translateFloorTypes() {
    floorTypesMap.emplace(GameType::FloorType::GRASS0,FloorTypeTexture{Grass,0});
    floorTypesMap.emplace(GameType::FloorType::GRASS1, FloorTypeTexture{Grass,1});
    floorTypesMap.emplace(GameType::FloorType::GRASS2, FloorTypeTexture{Grass,2});
    floorTypesMap.emplace(GameType::FloorType::GRASS3, FloorTypeTexture{Grass,3});
    floorTypesMap.emplace(GameType::FloorType::SAND, FloorTypeTexture{Sand,0});
    floorTypesMap.emplace(GameType::FloorType::WATER0, FloorTypeTexture{Water,0});
    floorTypesMap.emplace(GameType::FloorType::WATER1, FloorTypeTexture{Water,1});
    floorTypesMap.emplace(GameType::FloorType::WATER2, FloorTypeTexture{Water,2});
    floorTypesMap.emplace(GameType::FloorType::WATER3, FloorTypeTexture{Water,3});
    floorTypesMap.emplace(GameType::FloorType::PRETTY_ROAD0, FloorTypeTexture{PrettyRoad,0});
    floorTypesMap.emplace(GameType::FloorType::PRETTY_ROAD1, FloorTypeTexture{PrettyRoad,1});
    floorTypesMap.emplace(GameType::FloorType::PRETTY_ROAD2, FloorTypeTexture{PrettyRoad,2});
    floorTypesMap.emplace(GameType::FloorType::PRETTY_ROAD3, FloorTypeTexture{PrettyRoad,3});
    floorTypesMap.emplace(GameType::FloorType::PRETTY_GRASS0, FloorTypeTexture{PrettyGrass,0});
    floorTypesMap.emplace(GameType::FloorType::PRETTY_GRASS1, FloorTypeTexture{PrettyGrass,1});
    floorTypesMap.emplace(GameType::FloorType::PRETTY_GRASS2, FloorTypeTexture{PrettyGrass,2});
    floorTypesMap.emplace(GameType::FloorType::PRETTY_GRASS3, FloorTypeTexture{PrettyGrass,3});
    floorTypesMap.emplace(GameType::FloorType::DEAD_GRASS0, FloorTypeTexture{DeadGrass,0});
    floorTypesMap.emplace(GameType::FloorType::DEAD_GRASS1, FloorTypeTexture{DeadGrass,1});
    floorTypesMap.emplace(GameType::FloorType::DEAD_GRASS2, FloorTypeTexture{DeadGrass,2});
    floorTypesMap.emplace(GameType::FloorType::DEAD_GRASS3, FloorTypeTexture{DeadGrass,3});
    floorTypesMap.emplace(GameType::FloorType::DARK_WATER0, FloorTypeTexture{DarkWater,0});
    floorTypesMap.emplace(GameType::FloorType::DARK_WATER1, FloorTypeTexture{DarkWater,1});
    floorTypesMap.emplace(GameType::FloorType::DARK_WATER2, FloorTypeTexture{DarkWater,2});
    floorTypesMap.emplace(GameType::FloorType::DARK_WATER3, FloorTypeTexture{DarkWater,3});
}

void ProtocolEnumTranslator::_translateStructures() {
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
    structuresMap.emplace(GameType::Structure::NO_STRUCTURE, Nothing);
}

void ProtocolEnumTranslator::_translateRaces() {
    racesMap.emplace(GameType::Race::HUMAN, HumanHead);
    racesMap.emplace(GameType::Race::ELF, ElfHead);
    racesMap.emplace(GameType::Race::DWARF, DwarfHead);
    racesMap.emplace(GameType::Race::GNOME, GnomeHead);

}

void ProtocolEnumTranslator::_translateWeapons() {
    weaponsMap.emplace(GameType::Weapon::LONGSWORD, LongSword);
    weaponsMap.emplace(GameType::Weapon::AXE, Axe);
    weaponsMap.emplace(GameType::Weapon::WARHAMMER, WarHammer);
    weaponsMap.emplace(GameType::Weapon::ASH_ROD, AshRod);
    weaponsMap.emplace(GameType::Weapon::ELVEN_FLUTE, Nothing); //todo volar el elven flute solo
    weaponsMap.emplace(GameType::Weapon::LINKED_STAFF, LinkedStaff);
    weaponsMap.emplace(GameType::Weapon::SIMPLE_BOW, SimpleBow);
    weaponsMap.emplace(GameType::Weapon::COMPOSITE_BOW, CompositeBow);
    weaponsMap.emplace(GameType::Weapon::GNARLED_STAFF, GnarledStaff);
    weaponsMap.emplace(GameType::Weapon::FIST, Nothing);
}

void ProtocolEnumTranslator::_translateWeaponDrops() {
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

void ProtocolEnumTranslator::_translateClothing() {
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

void ProtocolEnumTranslator::_translateClothingDrops() {
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

void ProtocolEnumTranslator::_translatePotions() {
    potionsMap.emplace(GameType::Potion::HEALTH_POTION, HealthPotion);
    potionsMap.emplace(GameType::Potion::MANA_POTION, ManaPotion);
}

TextureID ProtocolEnumTranslator::getEntityTexture(GameType::Entity entity) {
    return entitiesMap.at(entity);
}

TextureID ProtocolEnumTranslator::getStructureTexture(GameType::Structure structure){
    return structuresMap.at(structure);
}
TextureID ProtocolEnumTranslator::getRaceTexture(GameType::Race race){
    return racesMap.at(race);
}
TextureID ProtocolEnumTranslator::getWeaponTexture(GameType::Weapon weapon){
    return weaponsMap.at(weapon);
}
TextureID ProtocolEnumTranslator::getWeaponDropTexture(GameType::Weapon weapon){
    return weaponDropsMap.at(weapon);
}
TextureID ProtocolEnumTranslator::getClothingTexture(GameType::Clothing clothing){
    return clothingMap.at(clothing);
}
TextureID ProtocolEnumTranslator::getClothingDropTexture(GameType::Clothing clothing){
    return clothingDropsMap.at(clothing);
}
TextureID ProtocolEnumTranslator::getPotionTexture(GameType::Potion potion){
    return potionsMap.at(potion);
}

FloorTypeTexture ProtocolEnumTranslator::getFloorTypeTexture(GameType::FloorType floorType) {
    return floorTypesMap.at(floorType);
}

ProtocolEnumTranslator::~ProtocolEnumTranslator() = default;
