//
// Created by ivan on 13/6/20.
//

#include "PlayerInventoryGUI.h"
#include "../GameConstants.h"

#define INVENTORY_SIZE 16 //////////////////////////////USAR EL GENERAL
#define LINES 4
#define COLUMNS 4

#define INVENTORY_ITEMS_X_OFFSET 20
#define INVENTORY_ITEMS_Y_OFFSET 150

#define ITEM_WIDTH 72
#define ITEM_HEIGHT 75

#define INVENTORY_OUTLINES_X_OFFSET 50
#define INVENTORY_OUTLINES_Y_OFFSET 175


PlayerInventoryGUI::PlayerInventoryGUI(TextureRepository &repo,
                                       SDL_Renderer &renderer) : repo(repo),
                                       renderer(renderer){
}

void PlayerInventoryGUI::render(){
    _drawInventoryOutlines();
    _drawEquipableOutlines();
    _renderInventoryItems();
    _renderEquipableItems();

}

void PlayerInventoryGUI::_renderInventoryItems(){
    unsigned int size = inventoryTextures.size();
    for (int i = 0; i < INVENTORY_SIZE; i += LINES) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (i + j >= (int)size) break;
            inventoryTextures[i + j]->render( INVENTORY_ITEMS_X_OFFSET +
            ITEM_WIDTH * j, INVENTORY_ITEMS_Y_OFFSET + (i/LINES) * ITEM_HEIGHT,
                    0,2);
        }
    }
}

void PlayerInventoryGUI::_renderEquipableItems(){
    if(equippedTextures.count(Helmet)){
        equippedTextures.at(Helmet)->render(115, 475,0,2);
    }
    if(equippedTextures.count(Shield)){
        equippedTextures.at(Shield)->render(40, 575, 0, 2);

    }
    if(equippedTextures.count(Armor)){
        equippedTextures.at(Armor)->render(115, 575, 0, 2);

    }
    if(equippedTextures.count(Weapon)){
        equippedTextures.at(Weapon)->render(192, 575, 0, 2);
    }
}

void PlayerInventoryGUI::_drawInventoryOutlines(){
    SDL_Rect outlineRect;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            outlineRect = { INVENTORY_OUTLINES_X_OFFSET + ITEM_WIDTH * j,
                            INVENTORY_OUTLINES_Y_OFFSET + ITEM_HEIGHT * i,
                            ITEM_WIDTH, ITEM_HEIGHT };
            SDL_SetRenderDrawColor( &renderer, 0x00,0x00,
                                    0x00, 0xFF );
            SDL_RenderDrawRect( &renderer, &outlineRect );
        }
    }
}

void PlayerInventoryGUI::_drawEquipableOutlines(){
    SDL_Rect outlineRect;
    for (int j = 0; j < 3; ++j) {
        outlineRect = { 70 + 75 * j, 600, ITEM_WIDTH, ITEM_HEIGHT };
        SDL_SetRenderDrawColor( &renderer, 0x00,0x00,
                                0x00, 0xFF );
        SDL_RenderDrawRect( &renderer, &outlineRect );
    }

    outlineRect = { 145, 500, ITEM_WIDTH, ITEM_HEIGHT };
    SDL_SetRenderDrawColor( &renderer, 0x00,0x00,
                            0x00, 0xFF );
    SDL_RenderDrawRect( &renderer, &outlineRect );
}



void PlayerInventoryGUI::addInventoryItem(TextureID texture) {
    //Ver si tengo q chequear tamaño
    inventoryTextures.push_back(&repo.getTexture(texture));
}

void PlayerInventoryGUI::addEquipableItem(TextureID texture, EquippedItems item){
    Texture* currTexture = &repo.getTexture(texture);
    equippedTextures.emplace(item, currTexture);
}

PlayerInventoryGUI::~PlayerInventoryGUI() {

}