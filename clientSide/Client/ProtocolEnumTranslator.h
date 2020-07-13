//
// Created by ivan on 25/6/20.
//

#ifndef ARGENTUM_PROTOCOLENUMTRANSLATOR_H
#define ARGENTUM_PROTOCOLENUMTRANSLATOR_H

#include "../../libs/GameEnums.h"
#include "../Texture/TextureRepository.h"
#include <unordered_map>

struct FloorTypeTexture{
    TextureID texture;
    int index;
};

class ProtocolEnumTranslator {
private:
    std::unordered_map<GameType::Entity,TextureID> entitiesMap;
    std::unordered_map<GameType::FloorType,FloorTypeTexture> floorTypesMap;
    std::unordered_map<GameType::Structure,TextureID> structuresMap;
    std::unordered_map<GameType::Race,TextureID> racesMap;
    std::unordered_map<GameType::Weapon,TextureID> weaponsMap;
    std::unordered_map<GameType::Weapon,TextureID> weaponDropsMap;
    std::unordered_map<GameType::Clothing,TextureID> clothingMap;
    std::unordered_map<GameType::Clothing,TextureID> clothingDropsMap;
    std::unordered_map<GameType::Potion,TextureID>potionsMap;

public:
    ProtocolEnumTranslator();
    TextureID getEntityTexture(GameType::Entity entity);
    FloorTypeTexture getFloorTypeTexture(GameType::FloorType entity);
    TextureID getStructureTexture(GameType::Structure structure);
    TextureID getRaceTexture(GameType::Race race);
    TextureID getWeaponTexture(GameType::Weapon weapon);
    TextureID getWeaponDropTexture(GameType::Weapon weapon);
    TextureID getClothingTexture(GameType::Clothing clothing);
    TextureID getClothingDropTexture(GameType::Clothing clothing);
    TextureID getPotionTexture(GameType::Potion potion);

    ~ProtocolEnumTranslator();

private:
    void _translateEntities();
    void _translateFloorTypes();
    void _translateStructures();
    void _translateRaces();
    void _translateWeapons();
    void _translateWeaponDrops();
    void _translateClothing();
    void _translateClothingDrops();
    void _translatePotions();
};


#endif //ARGENTUM_PROTOCOLENUMTRANSLATOR_H
