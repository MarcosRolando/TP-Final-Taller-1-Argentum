//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINVENTORYGUI_H
#define ARGENTUM_PLAYERINVENTORYGUI_H

#include "../Texture/TextureRepository.h"
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
    TextureRepository& repo;
    SDL_Renderer& renderer;
    std::vector<Texture*> inventoryTextures;
    std::unordered_map<EquippedItems, Texture*> equippedTextures;

public:
    PlayerInventoryGUI(TextureRepository& repo, SDL_Renderer& renderer);

    void addInventoryItem(TextureID texture);

    void addEquippedItem(TextureID texture, EquippedItems item);

    void render();

    ~PlayerInventoryGUI();

private:

    void _drawInventoryOutlines();

    void _renderInventoryItems();

    void _drawEquippedOutlines();

    void _renderEquippedItems();
};


#endif //ARGENTUM_PLAYERINVENTORYGUI_H
