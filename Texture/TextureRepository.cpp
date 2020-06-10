//
// Created by marcos on 9/6/20.
//

#include "TextureRepository.h"
#define BLUE_TUNIC_PATH "../Images/Clothing/BlueTunic.png"
#define COMMON_CLOTHING_PATH "../Images/Clothing/CommonClothing.png"
#define HOOD_PATH "../Images/Clothing/Hood.png"
#define IRON_HELMET_PATH "../Images/Clothing/IronHelmet.png"
#define IRON_SHIELD_PATH "../Images/Clothing/IronShield.png"
#define LEATHER_ARMOR_PATH "../Images/Clothing/LeatherArmor.png"
#define MAGIC_HAT_PATH "../Images/Clothing/MagicHat.png"
#define PLATE_ARMOR_PATH "../Images/Clothing/PlateArmor.png"
#define TURTLE_SHIELD_PATH "../Images/Clothing/TurtleShield.png"

TextureRepository::TextureRepository(SDL_Renderer& renderer) {
    _loadClothing(renderer);
}

void TextureRepository::_loadClothing(SDL_Renderer& renderer) {
    textures.emplace(BlueTunic, renderer);
    textures.emplace(CommonClothing, renderer);
    textures.emplace(Hood, renderer);
    textures.emplace(IronHelmet, renderer);
    textures.emplace(IronShield, renderer);
    textures.emplace(LeatherArmor, renderer);
    textures.emplace(MagicHat, renderer);
    textures.emplace(PlateArmor, renderer);
    textures.emplace(TurtleShield, renderer);
    Texture& texture = textures[BlueTunic];
    /*
    textures[CommonClothing].loadFromFile(COMMON_CLOTHING_PATH);
    textures[Hood].loadFromFile(HOOD_PATH);
    textures[IronHelmet].loadFromFile(IRON_HELMET_PATH);
    textures[IronShield].loadFromFile(IRON_SHIELD_PATH);
    textures[LeatherArmor].loadFromFile(LEATHER_ARMOR_PATH);
    textures[MagicHat].loadFromFile(MAGIC_HAT_PATH);
    textures[PlateArmor].loadFromFile(PLATE_ARMOR_PATH);
    textures[TurtleShield].loadFromFile(TURTLE_SHIELD_PATH);
     */
}
