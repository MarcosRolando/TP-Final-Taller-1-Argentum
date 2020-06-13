//
// Created by marcos on 9/6/20.
//

#ifndef ARGENTUM_TEXTUREREPOSITORY_H
#define ARGENTUM_TEXTUREREPOSITORY_H

#include <unordered_map>
#include "Texture.h"

enum TextureID {
    Nothing, /*Lo uso para el equipo del Player*/
    BlueTunic,
    BlueTunicDrop,
    CommonClothing,
    Hood,
    IronHelmet,
    IronShield,
    LeatherArmor,
    MagicHat,
    PlateArmor,
    TurtleShield,
    DwarfHead,
    ElfHead,
    GnomeHead,
    HumanHead,
    AshRod,
    Axe,
    CompoundBow,
    ElvenFlute,
    LinkedStaff,
    LongSword,
    LongSwordDrop,
    SimpleBow,
    WarHammer,
    Grass,
    Sand,
    Stone,
    Skeleton,
    Goblin,
    Zombie,
    Spider,
    Priest,
    Trader,
    Banker,
    Guard,
    Tree,
    LongTree,
    Bush,
    House1,
    House2,
    House3,
    Explosion0,
    Explosion1,
    Explosion2,
    Explosion3,
    Explosion4,
    Explosion5,
    Explosion6,
    Explosion7,
    Explosion8,
    Explosion9,
    Explosion10,
    Explosion11,
    Explosion12,
    Explosion13,
    Explosion14,
    Explosion15,
    Explosion16,
    Explosion17,
    Explosion18,
    Explosion19,
    Explosion20
};

class TextureRepository {
private:
    std::unordered_map<TextureID, Texture> textures;
    SDL_Renderer& renderer;

public:
    explicit TextureRepository(SDL_Renderer& renderer);
    Texture& getTexture(TextureID texture);

private:
    void _loadClothing();
    void _loadHeads();
    void _loadWeapons();
    void _loadTiles();
    void _loadStructures();
    void _loadNPCS();
    void _loadDrops();
    void _loadSpells();

    void _setImage(TextureID textureID, std::string&& structureImage,
                    int width, int height, int xOffset = 0, int yOffset = 0);
    void _setNPCImage(TextureID textureID, std::string&& npcImage, int width, int height
                                                , int xOffset = 0, int yOffset = 0);
    void _setBodyImage(TextureID texture, std::string&& bodyImage);
    void _setShieldImage(TextureID textureID, std::string&& shieldImage);
    void _setWeaponImage(TextureID textureID, std::string&& weaponImage);
    void _setTileImage(TextureID textureID, std::string&& tileImage, bool individualTile);
    void _setHeadImage(TextureID textureID, std::string&& headImage);
    void _setHelmetImage(TextureID textureID, std::string&& helmetImage,
                         int xOffset = 0, int yOffset = 0);

    static void _addBodySprites(Texture& texture, int y, bool lateralSide);
    static void _addWeaponSprites(Texture& texture, int y, bool lateralSide);
    static void _addShieldSprites(Texture& texture, int y, bool lateralSide);
    static void _addNPCSprites(Texture& texture, int y, bool lateralSide, int width, int height);
    static void _addTileSprites(Texture& texture, int y, bool individualTile);
    static void _addStructureSprites(Texture& texture, int width, int height);
};


#endif //ARGENTUM_TEXTUREREPOSITORY_H
