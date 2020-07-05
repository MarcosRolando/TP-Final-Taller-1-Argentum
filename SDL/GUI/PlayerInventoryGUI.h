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

class PlayerInventoryGUI {
private:
    Font textFont;
    Text text;
    TextureRepository& repo;
    SDL_Renderer& renderer;
    std::vector<Texture*> inventoryTextures;
    std::unordered_map<EquippedItems, Texture*> equippedTextures;
    PlayerInfoGUI& pInfo;
    int32_t gold;

public:
    PlayerInventoryGUI(TextureRepository& repo, SDL_Renderer& renderer, PlayerInfoGUI& playerInfo);
    void addInventoryItem(TextureID texture, int32_t slot);
    void addEquipableItem(TextureID texture, EquippedItems item);
    void updateGold(int32_t gold);
    void render(int32_t selectedSlot);

private:
    void _drawInventoryOutlines(int32_t x);
    void _renderInventoryItems();
    void _drawEquipableOutlines();
    void _renderEquipableItems();
    void _renderText();
    void _renderSkills();
};


#endif //ARGENTUM_PLAYERINVENTORYGUI_H
