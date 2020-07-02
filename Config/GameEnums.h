//
// Created by marcos on 20/6/20.
//

#ifndef ARGENTUM_GAMEENUMS_H
#define ARGENTUM_GAMEENUMS_H

#include <cinttypes>

namespace GameType {

    enum PlayerEvent : int32_t {
        MOVE, CREATE_PLAYER, LOAD_PLAYER
    };

    enum ID: int32_t {
        ENTITY, ITEM, PLAYER_DATA
    };

    enum EventID: int32_t {
        MOVED, ATTACK, UNEQUIP, USE_ITEM, DISAPPEARED, LIST
    };

    enum Race : int32_t {
        HUMAN, ELF, DWARF, GNOME
    };

    enum Class {
        WIZARD, CLERIC, PALADIN, WARRIOR
    };

    enum Entity: int32_t {
        SKELETON, ZOMBIE, SPIDER, GOBLIN, BANKER, GUARD, TRADER, PRIEST, PLAYER, NOTHING
    };

    enum ItemType: int32_t {
        ITEM_TYPE_GOLD, ITEM_TYPE_WEAPON, ITEM_TYPE_CLOTHING, ITEM_TYPE_POTION, ITEM_TYPE_NONE
    };

    enum Weapon: int32_t {
        LONGSWORD, AXE, WARHAMMER, ASH_ROD, ELVEN_FLUTE, LINKED_STAFF,
        SIMPLE_BOW, COMPOSITE_BOW, GNARLED_STAFF, FIST
    };

    enum Clothing: int32_t {
        COMMON_CLOTHING, LEATHER_ARMOR, PLATE_ARMOR, BLUE_TUNIC, HOOD,
        IRON_HELMET, TURTLE_SHIELD, IRON_SHIELD, MAGIC_HAT, NO_HELMET,
        NO_SHIELD
    };

    enum Potion: int32_t {
        HEALTH_POTION, MANA_POTION
    };

    enum FloorType: int32_t {
        GRASS0, GRASS1, GRASS2, GRASS3, SAND, WATER0, WATER1, WATER2, WATER3,
        PRETTY_ROAD0, PRETTY_ROAD1, PRETTY_ROAD2, PRETTY_ROAD3, PRETTY_GRASS0,
        PRETTY_GRASS1, PRETTY_GRASS2,PRETTY_GRASS3, DEAD_GRASS0, DEAD_GRASS1,
        DEAD_GRASS2, DEAD_GRASS3, DARK_WATER0, DARK_WATER1, DARK_WATER2, DARK_WATER3,
    };

    enum Structure: int32_t {
        BONE_GUY, BROKEN_RIP_STONE, BUSH, DEAD_BUSH, DEAD_GUY, DEAD_TREE,
        FAT_TREE, HANGED_GUY, HOUSE1, HOUSE2, HOUSE3, LONG_TREE, PALM_TREE,
        RIP_STONE, TREE, VERY_DEAD_GUY, SUNKEN_COLUMN, SUNKEN_SHIP, NO_STRUCTURE
    };

    enum Direction : int32_t {
        DIRECTION_UP, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT, DIRECTION_STILL
    };
}

#endif //ARGENTUM_GAMEENUMS_H
