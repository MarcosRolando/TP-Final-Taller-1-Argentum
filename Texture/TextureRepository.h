//
// Created by marcos on 9/6/20.
//

#ifndef ARGENTUM_TEXTUREREPOSITORY_H
#define ARGENTUM_TEXTUREREPOSITORY_H

#include <unordered_map>
#include "Texture.h"

enum TextureID {
    NOTHING, /*Lo uso para el equipo del Player*/
    BlueTunic,
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
    SimpleBow,
    WarHammer,
    Grass,
    Skeleton
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
    void _loadNPCS();
    void _setNPCImage(TextureID textureID, std::string&& npcImage);
    void _setBodyImage(TextureID texture, std::string&& bodyImage);
    void _setShieldImage(TextureID textureID, std::string&& shieldImage);
    void _setWeaponImage(TextureID textureID, std::string&& weaponImage);
    void _setTileImage(TextureID textureID, std::string&& tileImage);
    static void _addBodySprites(Texture& texture, int y, bool lateralSide);
    static void _addWeaponSprites(Texture& texture, int y, bool lateralSide);
    void _setHeadImage(TextureID textureID, std::string&& headImage);
    void _setHelmetImage(TextureID textureID, std::string&& helmetImage);
    static void _addShieldSprites(Texture& texture, int y, bool lateralSide);
    static void _addNPCSprites(Texture& texture, int y, bool lateralSide);
    static void _addTileSprites(Texture& texture, int y);
};


#endif //ARGENTUM_TEXTUREREPOSITORY_H
