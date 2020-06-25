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
    std::unordered_map<GameType::Race,TextureID> racesMap;
    std::unordered_map<GameType::Weapon,TextureID> weaponsMap;
    std::unordered_map<GameType::Weapon,TextureID> weaponDropsMap;
    std::unordered_map<GameType::Clothing,TextureID> clothingMap;
    std::unordered_map<GameType::Clothing,TextureID> clothingDropsMap;
    std::unordered_map<GameType::Potion,TextureID>potionsMap;

public:
    explicit ClientProtocol(Socket& _socket);
    void receiveMapInfo();

private:

    void _translateEntities();
    void _translateFloorTypes();
    void _translateStructures();
    void _translateRaces();
    void _translateWeapons();
    void _translateWeaponDrops();
    void _translateClothing();
    void _translatePotions();

    void _translateClothingDrops();
};


#endif //ARGENTUM_CLIENTPROTOCOL_H
