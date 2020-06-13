//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINVENTORYGUI_H
#define ARGENTUM_PLAYERINVENTORYGUI_H

#include "../Texture/TextureRepository.h"
#include <vector>

class PlayerInventoryGUI {
private:
    //Capaz le tengo q agregar un text
    TextureRepository& repo;
    SDL_Renderer& renderer;
    std::vector<Texture*> inventoryTextures;
    std::vector<Texture*> equippedTextures;

public:
    PlayerInventoryGUI(TextureRepository& repo, SDL_Renderer& renderer);

    void addItem(TextureID texture);

    void render();

    void _drawOutlines();

    ~PlayerInventoryGUI();

    void _renderItems();
};


#endif //ARGENTUM_PLAYERINVENTORYGUI_H
