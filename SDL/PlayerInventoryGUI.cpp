//
// Created by ivan on 13/6/20.
//

#include "PlayerInventoryGUI.h"
#include "../GameConstants.h"


PlayerInventoryGUI::PlayerInventoryGUI(TextureRepository &repo,
                                       SDL_Renderer &renderer) : repo(repo),
                                       renderer(renderer){
}

void PlayerInventoryGUI::render(){
    _drawInventoryOutlines();
    _drawEquippedOutlines();
    _renderInventoryItems();
    _renderEquippedItems();
}

void PlayerInventoryGUI::_renderInventoryItems(){
    unsigned int size = inventoryTextures.size();
    for (int i = 0; i < 16; i += 4) {
        for (int j = 0; j < 4; ++j) {
            if (i + j >= (int)size) break;
            inventoryTextures[i + j]->render(10 + 50 * j, 150 + (i/4) * 75,0,2);
        }
    }
}

void PlayerInventoryGUI::_renderEquippedItems(){
    //Siempre tiene que haber algo equipado
    equippedTextures.at(Helmet)->render(85, 475,0,2);
    equippedTextures.at(Shield)->render(10, 575, 0, 2);
    equippedTextures.at(Armor)->render(85, 575, 0, 2);
    equippedTextures.at(Weapon)->render(160, 575, 0, 2);
}

void PlayerInventoryGUI::_drawInventoryOutlines(){
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

void PlayerInventoryGUI::_drawEquippedOutlines(){
    SDL_Rect outlineRect;
    for (int j = 0; j < 3; ++j) {
        outlineRect = { 50 + 75 * j, 600, 50, 75 };
        SDL_SetRenderDrawColor( &renderer, 0x00,0x00,
                                0x00, 0xFF );
        SDL_RenderDrawRect( &renderer, &outlineRect );
    }

    outlineRect = { 125, 500, 50, 75 };
    SDL_SetRenderDrawColor( &renderer, 0x00,0x00,
                            0x00, 0xFF );
    SDL_RenderDrawRect( &renderer, &outlineRect );
}

PlayerInventoryGUI::~PlayerInventoryGUI() {

}

void PlayerInventoryGUI::addInventoryItem(TextureID texture) {
    //Ver si tengo q chequear tamaño
    inventoryTextures.push_back(&repo.getTexture(texture));
}

void PlayerInventoryGUI::addEquippedItem(TextureID texture, EquippedItems item){
    Texture* currTexture = &repo.getTexture(texture);
    equippedTextures.emplace(item, currTexture);
}

