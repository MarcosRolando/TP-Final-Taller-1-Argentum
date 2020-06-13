//
// Created by ivan on 13/6/20.
//

#include "PlayerInventoryGUI.h"
#include "../GameConstants.h"

PlayerInventoryGUI::PlayerInventoryGUI(TextureRepository &repo,
                                       SDL_Renderer &renderer) : repo(repo),
                                       renderer(renderer){
    /*for (int i = 0; i < 16; ++i) {
        addItem(Nothing);
    }*/
}

void PlayerInventoryGUI::render(){
    _drawOutlines();
    _renderItems();
}

void PlayerInventoryGUI::_renderItems(){
    unsigned int size = inventoryTextures.size();
    for (int i = 0; i < 16; i += 4) {
        for (int j = 0; j < 4; ++j) {
            inventoryTextures[i + j]->render(10 + 50 * j, 150 + (i/4) * 75,0,2);
        }
    }
}

void PlayerInventoryGUI::_drawOutlines(){
    SDL_Rect outlineRect;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            outlineRect = { 50 + 50 * j, 175 + 75 * i, 50, 75 };
            SDL_SetRenderDrawColor( &renderer, 0x00,0x00,
                                    0x00, 0xFF );
            SDL_RenderDrawRect( &renderer, &outlineRect );
        }
    }
}

PlayerInventoryGUI::~PlayerInventoryGUI() {

}

void PlayerInventoryGUI::addItem(TextureID texture) {
    //Ver si tengo q chequear tamaño
    inventoryTextures.push_back(&repo.getTexture(texture));
}
