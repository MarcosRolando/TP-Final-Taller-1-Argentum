//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINVENTORYGUI_H
#define ARGENTUM_PLAYERINVENTORYGUI_H

#include "../../Texture/TextureRepository.h"
#include "../Text/Text.h"
#include <vector>
#include <unordered_map>

enum EquippedItems{
    Helmet,
    Armor,
    Weapon,
    Shield,
};

class PlayerInventoryGUI {
private:
    //Capaz le tengo q agregar un text
    Text text;
    TextureRepository& repo;
    SDL_Renderer& renderer;
    std::vector<Texture*> inventoryTextures;
    std::unordered_map<EquippedItems, Texture*> equippedTextures;

public:
    PlayerInventoryGUI(TextureRepository& repo, SDL_Renderer& renderer, Font&
    font);

    void addInventoryItem(TextureID texture);

    void addEquipableItem(TextureID texture, EquippedItems item);

    void updateGold(unsigned int gold);

    void render();

private:

    void _drawInventoryOutlines();

    void _renderInventoryItems();

    void _drawEquipableOutlines();

    void _renderEquipableItems();

    void _renderText();
};


#endif //ARGENTUM_PLAYERINVENTORYGUI_H
