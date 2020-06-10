//
// Created by marcos on 9/6/20.
//

#ifndef ARGENTUM_TEXTUREREPOSITORY_H
#define ARGENTUM_TEXTUREREPOSITORY_H

#include <unordered_map>
#include "Texture.h"

const int TOTAL_TEXTURES = 23;

enum TextureID {
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

public:
    explicit TextureRepository(SDL_Renderer& renderer);

private:
    void _loadClothing(SDL_Renderer& renderer);
    void _loadHeads(SDL_Renderer& renderer);
    void _loadItems(SDL_Renderer& renderer);
    void _loadTiles(SDL_Renderer& renderer);
    void _loadMonsters(SDL_Renderer& renderer);
    void _setBodyImage(SDL_Renderer& renderer, TextureID texture, std::string&& bodyImage);
    static void _addBodySprites(Texture& texture, int y, bool lateralSide);
    void _setHeadImage(SDL_Renderer& renderer, TextureID textureID, std::string&& headImage);
};


#endif //ARGENTUM_TEXTUREREPOSITORY_H
