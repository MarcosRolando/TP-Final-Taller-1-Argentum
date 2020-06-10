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
#define DWARF_HEAD_PATH "../Images/Heads/DwarfHead.png"
#define ELF_HEAD_PATH "../Images/Heads/ElfHead.png"
#define GNOME_HEAD_PATH "../Images/Heads/GnomeHead.png"
#define HUMAN_HEAD_PATH "../Images/Heads/HumanHead.png"
#define ASH_ROD_PATH "../Images/Items/AshRod.png"
#define AXE_PATH "../Images/Items/Axe.png"
#define COMPOUND_BOW_PATH "../Images/Items/CompoundBow.png"
#define ELVEN_FLUTE_PATH "../Images/Items/ElvenFlute.png"
#define LINKED_STAFF_PATH "../Images/Items/LinkedStaff.png"
#define LONG_SWORD_PATH "../Images/Items/LongSword.png"
#define SIMPLE_BOW_PATH "../Images/Items/SimpleBow.png"
#define WAR_HAMMER_PATH "../Images/Items/WarHammer.png"
#define GRASS_PATH "../Images/Map/Grass.png"
#define SKELETON_PATH "../Images/Monsters/Skeleton.png"

TextureRepository::TextureRepository(SDL_Renderer& renderer) {
    _loadClothing(renderer);
    _loadHeads(renderer);
    _loadItems(renderer);
    _loadTiles(renderer);
    _loadMonsters(renderer);
}

void TextureRepository::_loadClothing(SDL_Renderer& renderer) {
    _setBodyImage(renderer, BlueTunic, BLUE_TUNIC_PATH);
    _setBodyImage(renderer, CommonClothing, BLUE_TUNIC_PATH);
    _setBodyImage(renderer, Hood, BLUE_TUNIC_PATH);
    _setBodyImage(renderer, IronHelmet, BLUE_TUNIC_PATH);
    _setBodyImage(renderer, IronShield, BLUE_TUNIC_PATH);
    _setBodyImage(renderer, LeatherArmor, BLUE_TUNIC_PATH);
    _setBodyImage(renderer, MagicHat, BLUE_TUNIC_PATH);
    _setBodyImage(renderer, PlateArmor, BLUE_TUNIC_PATH);
    _setBodyImage(renderer, TurtleShield, BLUE_TUNIC_PATH);
}

void TextureRepository::_loadHeads(SDL_Renderer& renderer) {
    _setHeadImage(renderer, DwarfHead, DWARF_HEAD_PATH);
    _setHeadImage(renderer, ElfHead, ELF_HEAD_PATH);
    _setHeadImage(renderer, GnomeHead, GNOME_HEAD_PATH);
    _setHeadImage(renderer, HumanHead, HUMAN_HEAD_PATH);
}

void TextureRepository::_loadItems(SDL_Renderer& renderer) {
    textures.emplace(AshRod, renderer);
    textures.emplace(Axe, renderer);
    textures.emplace(CompoundBow, renderer);
    textures.emplace(ElvenFlute, renderer);
    textures.emplace(LinkedStaff, renderer);
    textures.emplace(LongSword, renderer);
    textures.emplace(SimpleBow, renderer);
    textures.emplace(WarHammer, renderer);
    textures.at(AshRod).loadFromFile(ASH_ROD_PATH);
    textures.at(Axe).loadFromFile(AXE_PATH);
    textures.at(CompoundBow).loadFromFile(COMPOUND_BOW_PATH);
    textures.at(ElvenFlute).loadFromFile(ELVEN_FLUTE_PATH);
    textures.at(LinkedStaff).loadFromFile(LINKED_STAFF_PATH);
    textures.at(LongSword).loadFromFile(LONG_SWORD_PATH);
    textures.at(SimpleBow).loadFromFile(SIMPLE_BOW_PATH);
    textures.at(WarHammer).loadFromFile(WAR_HAMMER_PATH);
}

void TextureRepository::_loadTiles(SDL_Renderer& renderer) {
    textures.emplace(Grass, renderer);
    textures.at(Grass).loadFromFile(GRASS_PATH);
}

void TextureRepository::_loadMonsters(SDL_Renderer &renderer) {
    textures.emplace(Skeleton, renderer);
    textures.at(Skeleton).loadFromFile(SKELETON_PATH);
}

void TextureRepository::_setBodyImage(SDL_Renderer& renderer, TextureID textureID, std::string&& bodyImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(textureID, renderer);
        Texture& texture = textures.at(textureID);
        texture.loadFromFile(bodyImage, key);
        /*Front*/
        _addBodySprites(texture, 0, false);
        /*Back*/
        _addBodySprites(texture, 45, false);
        /*Left*/
        _addBodySprites(texture, 90, true);
        /*Rigth*/
        _addBodySprites(texture, 135, true);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void TextureRepository::_addBodySprites(Texture& texture, int y, bool lateralSide) {
    texture.addSprite(0, y, 24, 45); /*hasta 24 porque sino en la plate armor hay un poco de la otra imagen*/
    texture.addSprite(25, y, 25, 45);
    texture.addSprite(51, y, 24, 45); /*pongo 51 porque sino se veia un poco del pie de otro en algunas ropas*/
    texture.addSprite(75, y, 25, 45);
    texture.addSprite(100, y, 25, 45);
    if (lateralSide) texture.addSprite(100, y, 25, 45);
    else texture.addSprite(125, y, 25, 45);
}

void TextureRepository::_setHeadImage(SDL_Renderer& renderer, TextureID textureID, std::string&& headImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(textureID, renderer);
        Texture& texture = textures.at(textureID);
        texture.loadFromFile(headImage, key);
        texture.addSprite(0, 0, 17, 15);
        texture.addSprite(17, 0, 17, 15);
        texture.addSprite(34, 0, 17, 15);
        texture.addSprite(51, 0, 17, 15);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}
