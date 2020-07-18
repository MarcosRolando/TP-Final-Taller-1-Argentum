//
// Created by marcos on 7/5/20.
//

#ifndef ARGENTUM_PLAYERDATA_HPP
#define ARGENTUM_PLAYERDATA_HPP

#include <string>
#include "../../libs/GameEnums.h"
#include <vector>
#include <unordered_map>
#include <msgpack.hpp>

const int INVENTORY_SIZE = 16;
const int BANK_SIZE = 20;
const int MAX_NICKNAME_SIZE = 15;

struct PlayerData {
    bool isNewPlayer{false};
    std::string nickname;
    GameType::Race pRace{};
    GameType::Class pClass{};
    int32_t level{1};
    int32_t experience{0};
    int32_t gold{0};
    int32_t constitution{0}, strength{0}, agility{0}, intelligence{0};
    std::vector<std::tuple<GameType::ItemType, int32_t>> inventory;
    std::unordered_map<GameType::EquipmentPlace, int32_t> equipment;
    std::vector<std::tuple<GameType::ItemType, int32_t>> bankerItems;
    int32_t bankerGold{0};

    int32_t mySize{};

    PlayerData() {
        for (int i = 0; i < INVENTORY_SIZE; ++i) {
            inventory.emplace_back(std::tuple<GameType::ItemType, int32_t>(
                                    GameType::ITEM_TYPE_NONE, 0));
        }
        for (int i = 0; i < BANK_SIZE; ++i) {
            bankerItems.emplace_back(std::tuple<GameType::ItemType, int32_t>(
                    GameType::ITEM_TYPE_NONE, 0));
        }
        equipment.emplace(GameType::EQUIPMENT_PLACE_HEAD, GameType::NO_HELMET);
        equipment.emplace(GameType::EQUIPMENT_PLACE_CHEST, GameType::COMMON_CLOTHING);
        equipment.emplace(GameType::EQUIPMENT_PLACE_SHIELD, GameType::NO_SHIELD);
        equipment.emplace(GameType::EQUIPMENT_PLACE_WEAPON, GameType::FIST);
        mySize = MAX_NICKNAME_SIZE*sizeof(char) + sizeof(pRace) + sizeof(pClass) +
                         sizeof(level) + sizeof(experience) + sizeof(gold) +
                         sizeof(constitution) + sizeof(strength) + sizeof(agility) +
                         sizeof(intelligence) + sizeof(std::tuple<GameType::ItemType, int32_t>)*INVENTORY_SIZE +
                         + sizeof(std::tuple<GameType::ItemType, int32_t>)*BANK_SIZE +
                         + sizeof(bankerGold) + sizeof(int32_t)*4; /*Los 4 items equipados*/
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
        bankerItems = std::move(other.bankerItems);
        bankerGold = other.bankerGold;
        constitution = other.constitution;
        intelligence = other.intelligence;
        strength = other.strength;
        agility = other.agility;
        mySize = other.mySize;
        other.mySize = 0;
        isNewPlayer = other.isNewPlayer;
    }

    PlayerData& operator=(PlayerData&& other) noexcept {
        nickname = std::move(other.nickname);
        pRace = other.pRace;
        pClass = other.pClass;
        level = other.level;
        experience = other.experience;
        gold = other.gold;
        inventory = std::move(other.inventory);
        equipment = std::move(other.equipment);
        bankerItems = std::move(other.bankerItems);
        bankerGold = other.bankerGold;
        constitution = other.constitution;
        intelligence = other.intelligence;
        strength = other.strength;
        agility = other.agility;
        mySize = other.mySize;
        other.mySize = 0;
        isNewPlayer = other.isNewPlayer;
        return *this;
    }

    PlayerData(std::string&& _nickname, GameType::Race _pRace, GameType::Class _pClass) : PlayerData() {
        nickname = std::move(_nickname);
        pRace = _pRace;
        pClass = _pClass;
        isNewPlayer = true;
    }

    int32_t size() const {
        return mySize;
    }
};

#endif //ARGENTUM_PLAYERDATA_HPP
