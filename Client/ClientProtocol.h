//
// Created by ivan on 24/6/20.
//

#ifndef ARGENTUM_CLIENTPROTOCOL_H
#define ARGENTUM_CLIENTPROTOCOL_H

#include "GameGUI.h"
#include "../Shared/GameEnums.h"

class Socket;

class ClientProtocol {
private:
    GameGUI game;
    Socket& socket;
    std::unordered_map<GameType::Entity,TextureID> entitiesMap;
    std::unordered_map<GameType::FloorType,TextureID> floorTypesMap;
    std::unordered_map<GameType::Structure,TextureID> structuresMap;

public:
    explicit ClientProtocol(Socket& _socket);
    void receiveMapInfo();

    void _translateEntities();

    void _translateFloorTypes();

    void _translateStructures();
};


#endif //ARGENTUM_CLIENTPROTOCOL_H
