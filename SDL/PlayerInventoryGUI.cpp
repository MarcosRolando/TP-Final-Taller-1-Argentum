//
// Created by ivan on 13/6/20.
//

#include "PlayerInventoryGUI.h"

PlayerInventoryGUI::PlayerInventoryGUI(TextureRepository &repo,
                                       SDL_Renderer &renderer) : repo(repo),
                                       renderer(renderer){}

void PlayerInventoryGUI::render(){
    _drawOutlines();

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
