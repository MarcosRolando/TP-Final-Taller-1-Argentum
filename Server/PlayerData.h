//
// Created by marcos on 7/5/20.
//

#ifndef ARGENTUM_PLAYERDATA_H
#define ARGENTUM_PLAYERDATA_H

#include <string>
#include "../Config/GameEnums.h"

struct PlayerData {
    std::string nickname;
    GameType::Race pRace;
    GameType::Class pClass;
    int32_t level{};
    int32_t experience{};
    int32_t gold{};
    std::vector<std::tuple<GameType::ItemType, int32_t>> inventory;
    std::unordered_map<GameType::EquipmentPlace, int32_t> equipment; //todo habria que ver el tema del banker

    PlayerData(PlayerData&& other) noexcept {
        nickname = std::move(other.nickname);
        pRace = other.pRace;
        pClass = other.pClass;
        level = other.level;
        experience = other.experience;
        gold = other.gold;
        inventory = std::move(other.inventory);
        equipment = std::move(other.equipment);
    }

    PlayerData(std::string&& _nickname, GameType::Race _pRace, GameType::Class _pClass) {
        nickname = std::move(_nickname);
        pRace = _pRace;
        pClass = _pClass;
    }
};

#endif //ARGENTUM_PLAYERDATA_H
