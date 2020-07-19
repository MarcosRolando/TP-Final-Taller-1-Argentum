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

    /* Devuelve el id de la textura perteneciente a "entity" */
    TextureID getEntityTexture(GameType::Entity entity);

    /* Devuelve el id de la textura perteneciente a "floorType". Tambien recibe el
     * indice para saber que tile de la textura usar */
    FloorTypeTexture getFloorTypeTexture(GameType::FloorType floorType);

    /* Devuelve el id de la textura perteneciente a "structure" */
    TextureID getStructureTexture(GameType::Structure structure);

    /* Devuelve el id de la textura perteneciente a la raza "race" */
    TextureID getRaceTexture(GameType::Race race);

    /* Devuelve el id de la textura perteneciente a "weapon". Esta es la textura
     * que se usa para mostrar equipada en el jugador */
    TextureID getWeaponTexture(GameType::Weapon weapon);

    /* Devuelve el id de la textura perteneciente a "weapon". Esta es la textura
     * que se usa para mostrar como drop y en el inventario */
    TextureID getWeaponDropTexture(GameType::Weapon weapon);

    /* Devuelve el id de la textura perteneciente a la vestimenta "clothing". Esta es la textura
     * que se usa para mostrar equipada en el jugador */
    TextureID getClothingTexture(GameType::Clothing clothing);

    /* Devuelve el id de la textura perteneciente a "clothing". Esta es la textura
    * que se usa para mostrar como drop y en el inventario */
    TextureID getClothingDropTexture(GameType::Clothing clothing);

    /* Devuelve el id de la textura perteneciente a "potion" */
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
