//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINVENTORYGUI_H
#define ARGENTUM_PLAYERINVENTORYGUI_H

#include "../../Texture/TextureRepository.h"
#include "../Text/Text.h"
#include "PlayerInfoGUI.h"
#include <list>
#include <unordered_map>

enum EquippedItems{
    Helmet,
    Armor,
    Weapon,
    Shield,
};

class PlayerInventoryGUI {
private:
    Font textFont;
    Text text;
    TextureRepository& repo;
    SDL_Renderer& renderer;
    std::list<Texture*> inventoryTextures;
    std::unordered_map<EquippedItems, Texture*> equippedTextures;
    PlayerInfoGUI& pInfo;
    uint32_t gold;

public:
    PlayerInventoryGUI(TextureRepository& repo, SDL_Renderer& renderer, PlayerInfoGUI& playerInfo);
    void addInventoryItem(TextureID texture);
    void addEquipableItem(TextureID texture, EquippedItems item);
    void removeInventoryItem(int inventorySlot);
    void updateGold(unsigned int gold);
    void render(int selectedSlot);

private:
    void _drawInventoryOutlines(int x);
    void _renderInventoryItems();
    void _drawEquipableOutlines();
    void _renderEquipableItems();
    void _renderText();
    void _renderSkills();
};


#endif //ARGENTUM_PLAYERINVENTORYGUI_H
