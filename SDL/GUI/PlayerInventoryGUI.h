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
    /*void updateLevel(uint32_t newLevel);
    void updatePosition(int32_t x, int32_t y);
    //Capaz conviene hacer una que le sume 1 a todas las skills y listo
    void updateStrength(uint32_t strength);
    void updateConstitution(uint32_t constitution);
    void updateAgility(uint32_t agility);
    void updateIntelligence(uint32_t intelligence);*/
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
