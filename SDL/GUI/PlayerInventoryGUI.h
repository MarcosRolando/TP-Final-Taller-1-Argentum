//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINVENTORYGUI_H
#define ARGENTUM_PLAYERINVENTORYGUI_H

#include "../../Texture/TextureRepository.h"
#include "../Text/Text.h"
#include <list>
#include <unordered_map>

enum EquippedItems{
    Helmet,
    Armor,
    Weapon,
    Shield,
};

struct PlayerInfo {
    uint32_t level, gold;
    uint32_t constitution, strength, agility, intelligence;
    uint32_t xPos, yPos;
};

class PlayerInventoryGUI {
private:
    Font textFont;
    Text text;
    TextureRepository& repo;
    SDL_Renderer& renderer;
    std::list<Texture*> inventoryTextures;
    std::unordered_map<EquippedItems, Texture*> equippedTextures;
    PlayerInfo pInfo{};

public:
    PlayerInventoryGUI(TextureRepository& repo, SDL_Renderer& renderer);

    void addInventoryItem(TextureID texture);

    void addEquipableItem(TextureID texture, EquippedItems item);

    void updateGold(unsigned int gold);

    void render(int selectedSlot);

    void removeInventoryItem(int inventorySlot);

    void updateLevel(uint32_t newLevel);
    void updatePosition(int32_t x, int32_t y);
    void updateStrength(uint32_t strength);
    void updateConstitution(uint32_t constitution);
    void updateAgility(uint32_t agility);
    void updateIntelligence(uint32_t intelligence);


private:

    void _drawInventoryOutlines(int x);

    void _renderInventoryItems();

    void _drawEquipableOutlines();

    void _renderEquipableItems();

    void _renderText();
};


#endif //ARGENTUM_PLAYERINVENTORYGUI_H
