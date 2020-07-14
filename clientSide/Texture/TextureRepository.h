//
// Created by marcos on 9/6/20.
//

#ifndef ARGENTUM_TEXTUREREPOSITORY_H
#define ARGENTUM_TEXTUREREPOSITORY_H

#include <unordered_map>
#include "Texture.h"
#include "TextureID.h"


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
    void _loadMiscellaneous();
    void _loadUI();

    void _setImage(TextureID TextureID, std::string&& image,
                    int width, int height, int xOffset = 0, int yOffset = 0, int scale = 1
                            , ColorKey_t key = {0, 0, 0});
    void _setSpellImage(TextureID TextureID, std::string&& spellImage,
                            int width, int height, int xOffset = 0, int yOffset = 0);
    void _setNPCImage(TextureID TextureID, std::string&& npcImage, int width, int height
                                                , int xOffset = 0, int yOffset = 0);
    void _setBodyImage(TextureID texture, std::string&& bodyImage);
    void _setShieldImage(TextureID TextureID, std::string&& shieldImage);
    void _setWeaponImage(TextureID TextureID, std::string&& weaponImage);
    void _setTileImage(TextureID TextureID, std::string&& tileImage, bool individualTile);
    void _setHeadImage(TextureID TextureID, std::string&& headImage);
    void _setHelmetImage(TextureID TextureID, std::string&& helmetImage,
                         int xOffset = 0, int yOffset = 0);

    static void _addBodySprites(Texture& texture, int y, bool lateralSide);
    static void _addWeaponSprites(Texture& texture, int y, bool lateralSide);
    static void _addShieldSprites(Texture& texture, int y, bool lateralSide);
    static void _addNPCSprites(Texture& texture, int y, bool lateralSide, int width, int height);
    static void _addTileSprites(Texture& texture, int y, bool individualTile);
    static void _addStructureSprites(Texture& texture, int width, int height);
    static void _addSpellSprites(Texture& texture, int y, int width, int height);
};


#endif //ARGENTUM_TEXTUREREPOSITORY_H
