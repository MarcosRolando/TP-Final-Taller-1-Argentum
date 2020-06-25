//
// Created by marcos on 9/6/20.
//

#include "TextureRepository.h"
#include "../GameConstants.h"

#define BLUE_TUNIC_PATH "../Images/Clothing/BlueTunic.png"
#define BLUE_TUNIC_DROP_PATH "../Images/Clothing/BlueTunicDrop.png"
#define COMMON_CLOTHING_PATH "../Images/Clothing/CommonClothing.png"
#define COMMON_CLOTHING_DROP_PATH "../Images/Clothing/CommonClothingDrop.png"
#define HOOD_PATH "../Images/Clothing/Hood.png"
#define HOOD_DROP_PATH "../Images/Clothing/HoodDrop.png"
#define IRON_HELMET_PATH "../Images/Clothing/IronHelmet.png"
#define IRON_HELMET_DROP_PATH "../Images/Clothing/IronHelmetDrop.png"
#define IRON_SHIELD_PATH "../Images/Clothing/IronShield.png"
#define IRON_SHIELD_DROP_PATH "../Images/Clothing/IronShieldDrop.png"
#define KING_ARMOR_PATH "../Images/Clothing/KingArmor.png"
#define KING_ARMOR_DROP_PATH "../Images/Clothing/KingArmorDrop.png"
#define LEATHER_ARMOR_PATH "../Images/Clothing/LeatherArmor.png"
#define LEATHER_ARMOR_DROP_PATH "../Images/Clothing/LeatherArmorDrop.png"
#define MAGIC_HAT_PATH "../Images/Clothing/MagicHat.png"
#define MAGIC_HAT_DROP_PATH "../Images/Clothing/MagicHatDrop.png"
#define PLATE_ARMOR_PATH "../Images/Clothing/PlateArmor.png"
#define PLATE_ARMOR_DROP_PATH "../Images/Clothing/PlateArmorDrop.png"
#define TURTLE_SHIELD_PATH "../Images/Clothing/TurtleShield.png"
#define TURTLE_SHIELD_DROP_PATH "../Images/Clothing/TurtleShieldDrop.png"
#define DWARF_HEAD_PATH "../Images/Heads/DwarfHead.png"
#define ELF_HEAD_PATH "../Images/Heads/ElfHead.png"
#define GNOME_HEAD_PATH "../Images/Heads/GnomeHead.png"
#define HUMAN_HEAD_PATH "../Images/Heads/HumanHead.png"
#define ASH_ROD_PATH "../Images/Items/AshRod.png"
#define ASH_ROD_DROP_PATH "../Images/Items/AshRodDrop.png"
#define AXE_PATH "../Images/Items/Axe.png"
#define AXE_DROP_PATH "../Images/Items/AxeDrop.png"
#define COMPOUND_BOW_PATH "../Images/Items/CompositeBow.png"
#define COMPOUND_BOW_DROP_PATH "../Images/Items/CompositeBowDrop.png"
#define ELVEN_FLUTE_PATH "../Images/Items/ElvenFlute.png"
#define ELVEN_FLUTE_DROP_PATH "../Images/Items/ElvenFluteDrop.png"
#define LINKED_STAFF_PATH "../Images/Items/LinkedStaff.png"
#define LINKED_STAFF_DROP_PATH "../Images/Items/LinkedStaffDrop.png"
#define GNARLED_STAFF_PATH "../Images/Items/GnarledStaff.png"
#define GNARLED_STAFF_DROP_PATH "../Images/Items/GnarledStaffDrop.png"
#define LONG_SWORD_PATH "../Images/Items/LongSword.png"
#define LONG_SWORD_DROP_PATH "../Images/Items/LongSwordDrop.png"
#define SIMPLE_BOW_PATH "../Images/Items/SimpleBow.png"
#define SIMPLE_BOW_DROP_PATH "../Images/Items/SimpleBowDrop.png"
#define WAR_HAMMER_PATH "../Images/Items/WarHammer.png"
#define WAR_HAMMER_DROP_PATH "../Images/Items/WarHammerDrop.png"
#define HEALTH_POTION_PATH "../Images/Items/HealthPotion.png"
#define MANA_POTION_PATH "../Images/Items/ManaPotion.png"
#define GRASS_PATH "../Images/Map/Grass.png"
#define PRETTY_GRASS_PATH "../Images/Map/PrettyGrass.png"
#define PRETTY_ROAD_PATH "../Images/Map/PrettyRoad.png"
#define DEAD_GRASS_PATH "../Images/Map/DeadGrass.png"
#define SAND_PATH "../Images/Map/Sand.png"
#define WATER_PATH "../Images/Map/Water.png"
#define DARK_WATER_PATH "../Images/Map/DarkWater.png"
#define SKELETON_PATH "../Images/Monsters/Skeleton.png"
#define GOBLIN_PATH "../Images/Monsters/Goblin.png"
#define ZOMBIE_PATH "../Images/Monsters/Zombie.png"
#define SPIDER_PATH "../Images/Monsters/Spider.png"
#define PRIEST_PATH "../Images/Citizens/Priest.png"
#define TRADER_PATH "../Images/Citizens/Trader.png"
#define BANKER_PATH "../Images/Citizens/Banker.png"
#define GUARD_PATH "../Images/Citizens/Guard.png"
#define TREE_PATH "../Images/Map/Tree.png"
#define LONG_TREE_PATH "../Images/Map/LongTree.png"
#define FAT_TREE_PATH "../Images/Map/FatTree.png"
#define PALM_TREE_PATH "../Images/Map/PalmTree.png"
#define DEAD_TREE_PATH "../Images/Map/DeadTree.png"
#define BUSH_PATH "../Images/Map/Bush.png"
#define DEAD_BUSH_PATH "../Images/Map/DeadBush.png"
#define HOUSE1_PATH "../Images/Map/House1.png"
#define HOUSE2_PATH "../Images/Map/House2.png"
#define HOUSE3_PATH "../Images/Map/House3.png"
#define SUNKEN_COLUMN_PATH "../Images/Map/SunkenColumn.png"
#define SUNKEN_SHIP_PATH "../Images/Map/SunkenShip.png"
#define BONE_GUY_PATH "../Images/Map/BoneGuy.png"
#define BROKEN_RIP_STONE_PATH "../Images/Map/BrokenRipStone.png"
#define DEAD_GUY_PATH "../Images/Map/DeadGuy.png"
#define VERY_DEAD_GUY_PATH "../Images/Map/VeryDeadGuy.png"
#define HANGED_GUY_PATH "../Images/Map/HangedGuy.png"
#define RIP_STONE_PATH "../Images/Map/RipStone.png"
#define EXPLOSION_PATH "../Images/Spells/Explosion.png"
#define MAGIC_ARROW_PATH "../Images/Spells/MagicArrow.png"
#define MAGIC_MISSILE_PATH "../Images/Spells/MagicMissile.png"
#define HEAL_PATH "../Images/Spells/Heal.png"
#define BACKGROUND_PATH "../Images/UI/Background.png"
#define MAIN_MENU_PATH "../Images/UI/MainMenuTest.png"

TextureRepository::TextureRepository(SDL_Renderer& renderer) : renderer(renderer) {
    _loadClothing();
    _loadHeads();
    _loadWeapons();
    _loadTiles();
    _loadStructures();
    _loadNPCS();
    _loadDrops();
    _loadSpells();
    _loadUI();
}

void TextureRepository::_loadUI() {
    _setImage(Background, BACKGROUND_PATH, 1495, 937, 0
            , 0, 1, {-1, -1, -1});
    _setImage(MainMenu, MAIN_MENU_PATH, 1494, 934, 0,
            0, 1, {-1, -1, -1});
}

void TextureRepository::_loadSpells() {
    _setSpellImage(Explosion, EXPLOSION_PATH, 256, 256, -10, -10);
    _setSpellImage(MagicArrow, MAGIC_ARROW_PATH, 96, 100, 20, 15);
    _setSpellImage(MagicMissile, MAGIC_MISSILE_PATH, 128, 128, 8, 5);
    _setSpellImage(Heal, HEAL_PATH, 76, 76, 25, 20);
}

void TextureRepository::_loadDrops() {
    _setImage(BlueTunicDrop, BLUE_TUNIC_DROP_PATH, 32, 32, 30, 30, 2);
    _setImage(LongSwordDrop, LONG_SWORD_DROP_PATH, 32, 32, 33, 30, 2);
    _setImage(LinkedStaffDrop, LINKED_STAFF_DROP_PATH, 32, 32, 30, 30, 2);
    _setImage(GnarledStaffDrop, GNARLED_STAFF_DROP_PATH, 32, 32, 35, 30, 2);
    _setImage(MagicHatDrop, MAGIC_HAT_DROP_PATH, 32, 32, 50, 45);
    _setImage(HealthPotion, HEALTH_POTION_PATH, 32, 32, 50, 45);
    _setImage(ManaPotion, MANA_POTION_PATH, 32, 32, 50, 45);
    _setImage(CommonClothingDrop, COMMON_CLOTHING_DROP_PATH, 32, 32, 35, 30, 2);
    _setImage(KingArmorDrop, KING_ARMOR_DROP_PATH, 32, 32, 35, 30, 2);
    _setImage(LeatherArmorDrop, LEATHER_ARMOR_DROP_PATH, 32, 32, 35, 30, 2);
    _setImage(PlateArmorDrop, PLATE_ARMOR_DROP_PATH, 16, 32, 48, 35, 2);
    _setImage(HoodDrop, HOOD_DROP_PATH, 32, 32, 50, 45);
    _setImage(IronHelmetDrop, IRON_HELMET_DROP_PATH, 32, 32, 50, 45);
    _setImage(IronShieldDrop, IRON_SHIELD_DROP_PATH, 32, 32, 35, 30, 2);
    _setImage(TurtleShieldDrop, TURTLE_SHIELD_DROP_PATH, 32, 32, 50, 45);
    _setImage(AshRodDrop, ASH_ROD_DROP_PATH, 32, 32, 35, 30, 2);
    _setImage(AxeDrop, AXE_DROP_PATH, 32, 32, 32, 30, 2);
    _setImage(CompositeBowDrop, COMPOUND_BOW_DROP_PATH, 32, 32, 32, 30, 2);
    _setImage(ElvenFluteDrop, ELVEN_FLUTE_DROP_PATH, 32, 32, 32, 30, 2);
    _setImage(SimpleBowDrop, SIMPLE_BOW_DROP_PATH, 32, 32, 32, 30, 2);
    _setImage(WarHammerDrop, WAR_HAMMER_DROP_PATH, 32, 32, 32, 28, 2);
}

void TextureRepository::_loadClothing() {
    _setBodyImage(BlueTunic, BLUE_TUNIC_PATH);
    _setBodyImage(CommonClothing, COMMON_CLOTHING_PATH);
    _setShieldImage(IronShield, IRON_SHIELD_PATH);
    _setBodyImage(LeatherArmor, LEATHER_ARMOR_PATH);
    _setBodyImage(PlateArmor, PLATE_ARMOR_PATH);
    _setBodyImage(KingArmor, KING_ARMOR_PATH);
    _setShieldImage(TurtleShield, TURTLE_SHIELD_PATH);
    _setHelmetImage(Hood, HOOD_PATH);
    _setHelmetImage(IronHelmet, IRON_HELMET_PATH);
    _setHelmetImage(MagicHat, MAGIC_HAT_PATH, -1, -24);
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
    _setWeaponImage(CompositeBow, COMPOUND_BOW_PATH);
    //_setWeaponImage(ElvenFlute, ELVEN_FLUTE_PATH); todo
    _setWeaponImage(LinkedStaff, LINKED_STAFF_PATH);
    _setWeaponImage(GnarledStaff, GNARLED_STAFF_PATH);
    _setWeaponImage(LongSword, LONG_SWORD_PATH);
    _setWeaponImage(SimpleBow, SIMPLE_BOW_PATH);
    _setWeaponImage(WarHammer, WAR_HAMMER_PATH);
}

void TextureRepository::_loadTiles() {
    _setTileImage(Grass, GRASS_PATH, false);
    _setTileImage(PrettyGrass, PRETTY_GRASS_PATH, false);
    _setTileImage(PrettyRoad, PRETTY_ROAD_PATH, false);
    _setTileImage(DeadGrass, DEAD_GRASS_PATH, false);
    _setTileImage(Water, WATER_PATH, false);
    _setTileImage(DarkWater, DARK_WATER_PATH, false);
    _setTileImage(Sand, SAND_PATH, true);
}

void TextureRepository::_loadStructures() {
    _setImage(Tree, TREE_PATH, 256, 256, -60, -180);
    _setImage(LongTree, LONG_TREE_PATH, 256, 256, -60, -180);
    _setImage(FatTree, FAT_TREE_PATH, 256, 256, -60, -180);
    _setImage(PalmTree, PALM_TREE_PATH, 256, 256, -60, -180);
    _setImage(DeadTree, DEAD_TREE_PATH, 256, 256, -60, -160);
    _setImage(Bush, BUSH_PATH, 75, 65, 30, 40);
    _setImage(BoneGuy, BONE_GUY_PATH, 75, 65, 30, 40);
    _setImage(BrokenRipStone, BROKEN_RIP_STONE_PATH, 75, 65, 30, 20);
    _setImage(DeadGuy, DEAD_GUY_PATH, 75, 65, 30, -60, 2);
    _setImage(VeryDeadGuy, VERY_DEAD_GUY_PATH, 75, 65, 0, 10, 2);
    _setImage(HangedGuy, HANGED_GUY_PATH, 75, 65, 5, -60, 2);
    _setImage(RipStone, RIP_STONE_PATH, 75, 65, 30, 40);
    _setImage(DeadBush, DEAD_BUSH_PATH, 75, 65, 30, 40);
    _setImage(House1, HOUSE1_PATH, 196, 200, 40, -150);
    _setImage(House2, HOUSE2_PATH, 181, 213, 40, -150);
    _setImage(House3, HOUSE3_PATH, 200, 239, 30, -165);
    _setImage(SunkenShip, SUNKEN_SHIP_PATH, 256, 256, -120, -10, 2);
    _setImage(SunkenColumn, SUNKEN_COLUMN_PATH, 256, 256, 5, -185);
}

void TextureRepository::_loadNPCS() {
    _setNPCImage(Skeleton, SKELETON_PATH, 25, 52);
    _setNPCImage(Goblin, GOBLIN_PATH, 24, 31, -5, 15);
    _setNPCImage(Zombie, ZOMBIE_PATH, 25, 45);
    _setNPCImage(Spider, SPIDER_PATH, 34, 34, -10, 18);
    _setNPCImage(Priest, PRIEST_PATH, 25, 45, 37, 33);
    _setNPCImage(Trader, TRADER_PATH, 24, 48,37, 33);
    _setNPCImage(Banker, BANKER_PATH, 25, 45, 37, 33);
    _setNPCImage(Guard, GUARD_PATH, 28, 52, 37, 33);
}

void TextureRepository::_setImage(TextureID TextureID, std::string&& image,
                    int width, int height, int xOffset, int yOffset, int scale, ColorKey_t key) {
    try {
        //Load sprite sheet texture
        textures.emplace(TextureID, renderer);
        Texture& texture = textures.at(TextureID);
        texture.loadFromFile(image, key, xOffset, yOffset, scale);
        _addStructureSprites(texture, width, height);
    } catch (TPException& e) {
        throw TPException("Failed to load %s sprite sheet texture!\n", image.c_str());
    }
}

void TextureRepository::_setSpellImage(TextureID TextureID, std::string&& spellImage,
                                           int width, int height, int xOffset, int yOffset) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(TextureID, renderer);
        Texture& texture = textures.at(TextureID);
        texture.loadFromFile(spellImage, key, xOffset, yOffset);
        _addSpellSprites(texture, 0, width, height);
        _addSpellSprites(texture, height, width, height);
        _addSpellSprites(texture, 2*height, width, height);
        _addSpellSprites(texture, 3*height, width, height);
    } catch (TPException& e) {
        throw TPException("Failed to load %s sprite sheet texture!\n", spellImage.c_str());
    }
}

void TextureRepository::_setTileImage(TextureID TextureID, std::string&& tileImage, bool individualTile) {
    try {
        //Load sprite sheet texture
        textures.emplace(TextureID, renderer);
        Texture& texture = textures.at(TextureID);
        texture.loadFromFile(tileImage);
        _addTileSprites(texture, 0, individualTile);
    } catch (TPException& e) {
        throw TPException("Failed to load %s sprite sheet texture!\n", tileImage.c_str());
    }
}

void TextureRepository::_setNPCImage(TextureID TextureID, std::string&& npcImage, int width, int height
                                        , int xOffset, int yOffset) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(TextureID, renderer);
        Texture& texture = textures.at(TextureID);
        texture.loadFromFile(npcImage, key, xOffset, yOffset);
        /*Front*/
        _addNPCSprites(texture, 0, false, width, height);
        /*Back*/
        _addNPCSprites(texture, height, false, width, height);
        /*Left*/
        _addNPCSprites(texture, 2*height, true, width, height);
        /*Rigth*/
        _addNPCSprites(texture, 3*height, true, width, height);
    } catch (TPException& e) {
        throw TPException("Failed to load %s sprite sheet texture!\n", npcImage.c_str());
    }
}

void TextureRepository::_addNPCSprites(Texture& texture, int y, bool lateralSide, int width, int height) {
    for (int i = 0; i < 5; ++i) {
        texture.addSprite(width*i, y, width, height);
    }
    if (lateralSide) texture.addSprite(4*width, y, width, height);
    else texture.addSprite(5*width, y, width, height);
}

void TextureRepository::_setBodyImage(TextureID TextureID, std::string&& bodyImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(TextureID, renderer);
        Texture& texture = textures.at(TextureID);
        texture.loadFromFile(bodyImage, key);
        /*Front*/
        _addBodySprites(texture, 0, false);
        /*Back*/
        _addBodySprites(texture, 45, false);
        /*Left*/
        _addBodySprites(texture, 90, true);
        /*Rigth*/
        _addBodySprites(texture, 135, true);
    } catch (TPException& e) {
        throw TPException("Failed to load %s sprite sheet texture!\n", bodyImage.c_str());
    }
}

void TextureRepository::_setWeaponImage(TextureID TextureID, std::string&& weaponImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(TextureID, renderer);
        Texture& texture = textures.at(TextureID);
        texture.loadFromFile(weaponImage, key);
        /*Front*/
        _addWeaponSprites(texture, 0, false);
        /*Back*/
        _addWeaponSprites(texture, 45, false);
        /*Left*/
        _addWeaponSprites(texture, 90, true);
        /*Rigth*/
        _addWeaponSprites(texture, 135, true);
    } catch (TPException& e) {
        throw TPException("Failed to load %s sprite sheet texture!\n", weaponImage.c_str());
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

void TextureRepository::_setHeadImage(TextureID TextureID, std::string&& headImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(TextureID, renderer);
        Texture& texture = textures.at(TextureID);
        texture.loadFromFile(headImage, key);
        texture.addSprite(0, 0, 17, 15);
        texture.addSprite(17, 0, 17, 15);
        texture.addSprite(34, 0, 17, 15);
        texture.addSprite(51, 0, 17, 15);
    } catch (TPException& e) {
        throw TPException("Failed to load %s sprite sheet texture!\n", headImage.c_str());
    }
}

void TextureRepository::_setHelmetImage(TextureID TextureID, std::string&& helmetImage,
                                                int xOffset, int yOffset) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(TextureID, renderer);
        Texture& texture = textures.at(TextureID);
        texture.loadFromFile(helmetImage, key, xOffset, yOffset);
        texture.addSprite(0, 0, 17, 17);
        texture.addSprite(17, 0, 17, 17);
        texture.addSprite(34, 0, 17, 17);
        texture.addSprite(51, 0, 17, 17);
    } catch (TPException& e) {
        throw TPException("Failed to load %s sprite sheet texture!\n", helmetImage.c_str());
    }
}

void TextureRepository::_setShieldImage(TextureID TextureID, std::string&& shieldImage) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        textures.emplace(TextureID, renderer);
        Texture& texture = textures.at(TextureID);
        texture.loadFromFile(shieldImage, key);
        /*Front*/
        _addShieldSprites(texture, 0, false);
        /*Back*/
        _addShieldSprites(texture, 45, false);
        /*Left*/
        _addShieldSprites(texture, 90, true);
        /*Rigth*/
        _addShieldSprites(texture, 135, true);
    } catch (TPException& e) {
        throw TPException("Failed to load %s sprite sheet texture!\n", shieldImage.c_str());
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

void TextureRepository::_addTileSprites(Texture& texture, int y, bool individualTile) {
    texture.addSprite(0, 0, TILE_WIDTH, TILE_HEIGHT);
    if (!individualTile) {
        texture.addSprite(TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT);
        texture.addSprite(2*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT);
        texture.addSprite(3*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT);
    }
}

void TextureRepository::_addStructureSprites(Texture& texture, int width, int height) {
    texture.addSprite(0, 0, width, height);
}

void TextureRepository::_addSpellSprites(Texture& texture, int y, int width, int height) {
    for (int i = 0; i < 6; ++i) {
        texture.addSprite(width*i, y, width, height);
    }
}

Texture& TextureRepository::getTexture(TextureID texture) {
    return textures.at(texture);
}
