//
// Created by marcos on 9/6/20.
//

#include "TextureRepository.h"
#include "../GameConstants.h"

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
#define GOBLIN_PATH "../Images/Monsters/Goblin.png"
#define ZOMBIE_PATH "../Images/Monsters/Zombie.png"
#define SPIDER_PATH "../Images/Monsters/Spider.png"

TextureRepository::TextureRepository(SDL_Renderer& renderer) : renderer(renderer) {
    _loadClothing();
    _loadHeads();
    _loadWeapons();
    _loadTiles();
    _loadNPCS();
}

void TextureRepository::_loadClothing() {
    _setBodyImage(BlueTunic, BLUE_TUNIC_PATH);
    _setBodyImage(CommonClothing, COMMON_CLOTHING_PATH);
    _setShieldImage(IronShield, IRON_SHIELD_PATH);
    _setBodyImage(LeatherArmor, LEATHER_ARMOR_PATH);
    _setBodyImage(PlateArmor, PLATE_ARMOR_PATH);
    _setShieldImage(TurtleShield, TURTLE_SHIELD_PATH);
    _setHelmetImage(Hood, HOOD_PATH);
    _setHelmetImage(IronHelmet, IRON_HELMET_PATH);
    _setHelmetImage(MagicHat, MAGIC_HAT_PATH);
}

void TextureRepository::_loadHeads() {
    _setHeadImage(DwarfHead, DWARF_HEAD_PATH);
    _setHeadImage(ElfHead, ELF_HEAD_PATH);
    _setHeadImage(GnomeHead, GNOME_HEAD_PATH);
    _setHeadImage(HumanHead, HUMAN_HEAD_PATH);
}

void TextureRepository::_loadWeapons() {
    _setWeaponImage(AshRod, ASH_ROD_PATH);
    _setWeaponImage(Axe, AXE_PATH);
    _setWeaponImage(CompoundBow, COMPOUND_BOW_PATH);
    _setWeaponImage(ElvenFlute, ELVEN_FLUTE_PATH);
    _setWeaponImage(LinkedStaff, LINKED_STAFF_PATH);
    _setWeaponImage(LongSword, LONG_SWORD_PATH);
    _setWeaponImage(SimpleBow, SIMPLE_BOW_PATH);
    _setWeaponImage(WarHammer, WAR_HAMMER_PATH);
}

void TextureRepository::_loadTiles() {
    _setTileImage(Grass, GRASS_PATH);
}

void TextureRepository::_loadNPCS() {
    _setNPCImage(Skeleton, SKELETON_PATH, 25, 52);
    _setNPCImage(Goblin, GOBLIN_PATH, 24, 31);
    _setNPCImage(Zombie, ZOMBIE_PATH, 25, 45);
    _setNPCImage(Spider, SPIDER_PATH, 34, 34);
}

void TextureRepository::_setTileImage(TextureID textureID, std::string&& tileImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(textureID, renderer);
        Texture& texture = textures.at(textureID);
        texture.loadFromFile(tileImage, key);
        _addTileSprites(texture, 0);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void TextureRepository::_setNPCImage(TextureID textureID, std::string&& npcImage, int width, int height) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(textureID, renderer);
        Texture& texture = textures.at(textureID);
        texture.loadFromFile(npcImage, key);
        /*Front*/
        _addNPCSprites(texture, 0, false, width, height);
        /*Back*/
        _addNPCSprites(texture, height, false, width, height);
        /*Left*/
        _addNPCSprites(texture, 2*height, true, width, height);
        /*Rigth*/
        _addNPCSprites(texture, 3*height, true, width, height);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void TextureRepository::_addNPCSprites(Texture& texture, int y, bool lateralSide, int width, int height) {
    texture.addSprite(0, y, width, height);
    texture.addSprite(width, y, width, height);
    texture.addSprite(2*width, y, width, height);
    texture.addSprite(3*width, y, width, height);
    texture.addSprite(4*width, y, width, height);
    if (lateralSide) texture.addSprite(4*width, y, width, height);
    else texture.addSprite(5*width, y, width, height);
}

void TextureRepository::_setBodyImage(TextureID textureID, std::string&& bodyImage) {
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

void TextureRepository::_setWeaponImage(TextureID textureID, std::string&& weaponImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(textureID, renderer);
        Texture& texture = textures.at(textureID);
        texture.loadFromFile(weaponImage, key);
        /*Front*/
        _addWeaponSprites(texture, 0, false);
        /*Back*/
        _addWeaponSprites(texture, 45, false);
        /*Left*/
        _addWeaponSprites(texture, 90, true);
        /*Rigth*/
        _addWeaponSprites(texture, 135, true);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void TextureRepository::_addWeaponSprites(Texture& texture, int y, bool lateralSide) {
    texture.addSprite(0, y, 24, 45);
    texture.addSprite(25, y, 25, 45);
    texture.addSprite(51, y - 1, 23, 45);
    texture.addSprite(76, y - 1, 23, 45);
    texture.addSprite(101, y - 1, 24, 45);
    if (lateralSide) texture.addSprite(101, y, 24, 45);
    else texture.addSprite(126, y, 25, 45);
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

void TextureRepository::_setHeadImage(TextureID textureID, std::string&& headImage) {
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

void TextureRepository::_setHelmetImage(TextureID textureID, std::string&& helmetImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(textureID, renderer);
        Texture& texture = textures.at(textureID);
        texture.loadFromFile(helmetImage, key);
        texture.addSprite(0, 0, 17, 17);
        texture.addSprite(17, 0, 17, 17);
        texture.addSprite(34, 0, 17, 17);
        texture.addSprite(51, 0, 17, 17);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void TextureRepository::_setShieldImage(TextureID textureID, std::string&& shieldImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(textureID, renderer);
        Texture& texture = textures.at(textureID);
        texture.loadFromFile(shieldImage, key);
        /*Front*/
        _addShieldSprites(texture, 0, false);
        /*Back*/
        _addShieldSprites(texture, 45, false);
        /*Left*/
        _addShieldSprites(texture, 90, true);
        /*Rigth*/
        _addShieldSprites(texture, 135, true);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void TextureRepository::_addShieldSprites(Texture& texture, int y, bool lateralSide) {
    texture.addSprite(0, y, 25, 35);
    texture.addSprite(26, y, 25, 35);
    texture.addSprite(51, y, 24, 35);
    texture.addSprite(76, y, 25, 35);
    texture.addSprite(101, y, 24, 35);
    if (lateralSide) texture.addSprite(101, y, 24, 35);
    else texture.addSprite(126, y, 25, 35);
}

void TextureRepository::_addTileSprites(Texture& texture, int y) {
    texture.addSprite(0, 0, TILE_WIDTH, TILE_HEIGHT);
    texture.addSprite(TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT);
    texture.addSprite(2*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT);
    texture.addSprite(3*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT);
}

Texture& TextureRepository::getTexture(TextureID texture) {
    return textures.at(texture);
}
