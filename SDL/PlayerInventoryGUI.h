//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINVENTORYGUI_H
#define ARGENTUM_PLAYERINVENTORYGUI_H

#include "../Texture/TextureRepository.h"

class PlayerInventoryGUI {
private:
    //Capaz le tengo q agregar un text
    TextureRepository& repo;
    SDL_Renderer& renderer;

public:
    PlayerInventoryGUI(TextureRepository& repo, SDL_Renderer& renderer);
    ~PlayerInventoryGUI();

    void render();

    void _drawOutlines();
};


#endif //ARGENTUM_PLAYERINVENTORYGUI_H
