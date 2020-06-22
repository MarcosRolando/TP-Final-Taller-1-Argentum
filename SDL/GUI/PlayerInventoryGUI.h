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

class PlayerInventoryGUI {
private:
    Text text;
    TextureRepository& repo;
    SDL_Renderer& renderer;
    //std::vector<Texture*> inventoryTextures;
    std::list<Texture*> inventoryTextures;
    std::unordered_map<EquippedItems, Texture*> equippedTextures;

public:
    PlayerInventoryGUI(TextureRepository& repo, SDL_Renderer& renderer, Font&
    font);

    void addInventoryItem(TextureID texture);

    void addEquipableItem(TextureID texture, EquippedItems item);

    void updateGold(unsigned int gold);

    void render(int selectedSlot);

    void removeInventoryItem(int inventorySlot);

private:

    void _drawInventoryOutlines(int x);

    void _renderInventoryItems();

    void _drawEquipableOutlines();

    void _renderEquipableItems();

    void _renderText();
};


#endif //ARGENTUM_PLAYERINVENTORYGUI_H
