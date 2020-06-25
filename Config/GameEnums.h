//
// Created by marcos on 20/6/20.
//

#ifndef ARGENTUM_GAMEENUMS_H
#define ARGENTUM_GAMEENUMS_H

#include <cinttypes>

namespace GameType {
    enum Race : int32_t {
        HUMAN, ELF, DWARF, GNOME
    };

    enum Class {
        WIZARD, CLERIC, PALADIN, WARRIOR
    };

    enum Entity: int32_t {
        SKELETON, ZOMBIE, SPIDER, GOBLIN, BANKER, GUARD, TRADER, PRIEST, PLAYER, NOTHING
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

    enum class FloorType: int32_t {
        GRASS, SAND, WATER, DARK_WATER, DEAD_GRASS, PRETTY_GRASS, WALL, TREE
    };
}

#endif //ARGENTUM_GAMEENUMS_H
