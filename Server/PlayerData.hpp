//
// Created by marcos on 7/5/20.
//

#ifndef ARGENTUM_PLAYERDATA_HPP
#define ARGENTUM_PLAYERDATA_HPP

#include <string>
#include "../Config/GameEnums.h"
#include <vector>
#include <unordered_map>
#include <msgpack.hpp>

const int INVENTORY_SIZE = 16;

struct PlayerData {
    std::string nickname;
    GameType::Race pRace{};
    GameType::Class pClass{};
    int32_t level{};
    int32_t experience{};
    int32_t gold{};
    int32_t constitution{}, strength{}, agility{}, intelligence{};
    std::vector<std::tuple<GameType::ItemType, int32_t>> inventory;
    std::unordered_map<GameType::EquipmentPlace, int32_t> equipment; //todo habria que ver el tema del banker

    PlayerData() {
        for (int i = 0; i < INVENTORY_SIZE; ++i) {
            inventory.emplace_back(std::tuple<GameType::ItemType, int32_t>(
                                    GameType::ITEM_TYPE_NONE, 0));
        }
        equipment.emplace(GameType::EQUIPMENT_PLACE_HEAD, 0);
        equipment.emplace(GameType::EQUIPMENT_PLACE_CHEST, 0);
        equipment.emplace(GameType::EQUIPMENT_PLACE_SHIELD, 0);
        equipment.emplace(GameType::EQUIPMENT_PLACE_WEAPON, 0);
    }

    PlayerData(PlayerData&& other) noexcept {
        nickname = std::move(other.nickname);
        pRace = other.pRace;
        pClass = other.pClass;
        level = other.level;
        experience = other.experience;
        gold = other.gold;
        inventory = std::move(other.inventory);
        equipment = std::move(other.equipment);
        constitution = other.constitution;
        intelligence = other.intelligence;
        strength = other.strength;
        agility = other.agility;
    }

    PlayerData(std::string&& _nickname, GameType::Race _pRace, GameType::Class _pClass) : PlayerData() {
        nickname = std::move(_nickname);
        pRace = _pRace;
        pClass = _pClass;
    }
};

#endif //ARGENTUM_PLAYERDATA_HPP
