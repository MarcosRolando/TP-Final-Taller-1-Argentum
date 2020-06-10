//
// Created by marcos on 9/6/20.
//

#ifndef ARGENTUM_TEXTUREREPOSITORY_H
#define ARGENTUM_TEXTUREREPOSITORY_H

#include <unordered_map>
#include "Texture.h"

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
    WarHammer
};

class TextureRepository {
private:
    std::unordered_map<TextureID, Texture> textures;

public:
    explicit TextureRepository(SDL_Renderer& renderer);

private:
    void _loadClothing(SDL_Renderer& renderer);
};


#endif //ARGENTUM_TEXTUREREPOSITORY_H
