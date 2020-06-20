//
// Created by marcos on 20/6/20.
//

#ifndef ARGENTUM_GAMEENUMS_H
#define ARGENTUM_GAMEENUMS_H

namespace GameType {
    enum Race {
        HUMAN, ELF, DWARF, GNOME
    };

    enum Class {
        WIZARD, CLERIC, PALADIN, WARRIOR
    };

    enum Monster {
        SKELETON, ZOMBIE, SPIDER, GOBLIN
    };

    enum Weapon {
        LONGSWORD, AXE, WARHAMMER, ASH_ROD, ELVEN_FLUTE, LINKED_STAFF,
        SIMPLE_BOW, COMPOSITE_BOW, GNARLED_STAFF, FIST
    };

    enum Clothing {
        COMMON_CLOTHING, LEATHER_ARMOR, PLATE_ARMOR, BLUE_TUNIC, HOOD,
        IRON_HELMET, TURTLE_SHIELD, IRON_SHIELD, MAGIC_HAT, NO_HELMET,
        NO_SHIELD
    };

    enum Potion {
        HEALTH_POTION, MANA_POTION
    };
}

#endif //ARGENTUM_GAMEENUMS_H
