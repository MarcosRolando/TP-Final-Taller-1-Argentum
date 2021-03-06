//
// Created by marcos on 7/2/20.
//

#ifndef ARGENTUM_ENTITYDATA_H
#define ARGENTUM_ENTITYDATA_H

#include <string>
#include "../Texture/TextureRepository.h"
#include "../Map/Coordinate.h"
#include "../../libs/GameEnums.h"
#include "../Graphics/GUI/PlayerStats.h"
#include "../Texture/PlayerEquipment.h"

/*La info de un player para cargar en el mapa, esto me llega cuando se
 * crea un nuevo player*/

struct EntityData {
    TextureID texture;
    std::string nickname;
    Coordinate pos;
    GameType::Direction currentDir;
    int32_t distanceMoved;
    int32_t level;
};

struct PlayerData {
    PlayerStats generalInfo;
    std::vector<std::tuple<TextureID, EquippedItems>> equippedItems;
    std::vector<std::tuple<TextureID, int>> inventoryItems;
    std::string minichatText;

    PlayerData(PlayerData&& other) noexcept {
        this->generalInfo = other.generalInfo;
        this->inventoryItems = std::move(other.inventoryItems);
        this->equippedItems = std::move(other.equippedItems);
        this->minichatText = std::move(other.minichatText);
        other.generalInfo = {};
        other.inventoryItems.clear();
        other.equippedItems.clear();
    }

    PlayerData() = default;
};

struct MapPlayerData {
    EntityData entityData;
    GameType::Race race{};
    PlayerEquipment equipment{};
    bool isAlive{};
};

struct ItemData {
    Coordinate position;
    TextureID texture;
};

#endif //ARGENTUM_ENTITYDATA_H
