//
// Created by marcos on 7/5/20.
//

#ifndef ARGENTUM_INITIALPLAYERDATA_H
#define ARGENTUM_INITIALPLAYERDATA_H

#include <string>
#include "../Config/GameEnums.h"

struct InitialPlayerData {
    std::string nickname;
    GameType::Race race; //todo habria que ver de agregarla mas cosas como inventario y eso cuando tengamos la persistencia
    GameType::Class _class;

    InitialPlayerData(InitialPlayerData&& other) noexcept {
        nickname = std::move(other.nickname);
        race = other.race;
        _class = other._class;
    }

    InitialPlayerData(std::string&& _nickname, GameType::Race _race, GameType::Class __class) {
        nickname = std::move(_nickname);
        race = _race;
        _class = __class;
    }
};

#endif //ARGENTUM_INITIALPLAYERDATA_H
