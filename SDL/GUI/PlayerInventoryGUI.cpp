//
// Created by ivan on 13/6/20.
//

#include "PlayerInventoryGUI.h"
#include "../../GameConstants.h"

#define INVENTORY_SIZE 16 //////////////////////////////USAR EL GENERAL
#define LINES 4
#define COLUMNS 4

#define INVENTORY_ITEMS_X_OFFSET 45
#define INVENTORY_ITEMS_Y_OFFSET 235

#define ITEM_WIDTH 72
#define ITEM_HEIGHT 75

#define INVENTORY_OUTLINES_X_OFFSET 73
#define INVENTORY_OUTLINES_Y_OFFSET 260


PlayerInventoryGUI::PlayerInventoryGUI(TextureRepository &repo,SDL_Renderer &renderer) :
                                        textFont("../SDL/Text/medieval.ttf", 25),
                                            text(textFont,renderer), repo(repo),
                                                             renderer(renderer) {

}

void PlayerInventoryGUI::render(int selectedSlotX) {
    _drawInventoryOutlines(selectedSlotX);
    _drawEquipableOutlines();
    _renderInventoryItems();
    _renderEquipableItems();
    _renderText();
}

void PlayerInventoryGUI::_renderInventoryItems() {
    int i = 0, j = 0; //los necesito para la posicion de renderizado
    for (auto & texture : inventoryTextures){
        texture->render(INVENTORY_ITEMS_X_OFFSET + (ITEM_WIDTH + 6) * j,
                INVENTORY_ITEMS_Y_OFFSET + (i/LINES) * (ITEM_HEIGHT - 1),0);
        //Esto lo haria con un for pero la lista no tiene operator[]
        ++j;
        if (j > 3) {
            i += LINES;
            j = 0;
        }
    }
}

void PlayerInventoryGUI::_renderEquipableItems() {
    if(equippedTextures.count(Helmet)){
        equippedTextures.at(Helmet)->render(250, 635,0);
    }
    if(equippedTextures.count(Armor)){
        equippedTextures.at(Armor)->render(325, 635, 0);

    }
    if(equippedTextures.count(Weapon)){
        equippedTextures.at(Weapon)->render(250, 735, 0);

    }
    if(equippedTextures.count(Shield)){
        equippedTextures.at(Shield)->render(325, 735, 0);
    }
}

void PlayerInventoryGUI::_drawInventoryOutlines(int selectedSlot) {
    SDL_Rect outlineRect;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            outlineRect = { INVENTORY_OUTLINES_X_OFFSET + (ITEM_WIDTH + 6) * j,
                            INVENTORY_OUTLINES_Y_OFFSET + (ITEM_HEIGHT - 3) * i,
                            ITEM_WIDTH + 6, ITEM_HEIGHT - 3 };
            SDL_SetRenderDrawColor(&renderer, 0x3f, 0x2a,
                                   0x14, 0xFF);
            if ((j + 4 * i) == selectedSlot){
                SDL_SetRenderDrawColor(&renderer, 0xff, 0xff,
                                       0xff, 0xFF);
            }
            SDL_RenderDrawRect( &renderer, &outlineRect );
        }
    }
}

void PlayerInventoryGUI::_drawEquipableOutlines() {
    SDL_Rect outlineRect;
    for (int j = 0; j < 2; ++j) {
        outlineRect = { 275 + 75 * j, 660, ITEM_WIDTH, ITEM_HEIGHT };
        SDL_SetRenderDrawColor( &renderer, 0x3f,0x2a,
                                0x14, 0xFF );
        SDL_RenderDrawRect( &renderer, &outlineRect );
    }
    for (int j = 0; j < 2; ++j) {
        outlineRect = { 275 + 75 * j, 760, ITEM_WIDTH, ITEM_HEIGHT };
        SDL_SetRenderDrawColor( &renderer, 0x3f,0x2a,
                                0x14, 0xFF );
        SDL_RenderDrawRect( &renderer, &outlineRect );
    }

}

void PlayerInventoryGUI::addInventoryItem(TextureID texture) {
    if (inventoryTextures.size() < INVENTORY_SIZE) {
        inventoryTextures.push_back(&repo.getTexture(texture));
    }
}

void PlayerInventoryGUI::removeInventoryItem(int inventorySlot) {
    int i = 0, j = 0;
    for (auto it = inventoryTextures.begin(); it != inventoryTextures.end(); ) {
        //Esto lo haria con un for pero la lista no tiene operator[]
        if (j > 3) {
            i += LINES;
            j = 0;
        }
        if ((j + i) == inventorySlot){
            it = inventoryTextures.erase(it);
        } else {
            ++it;
        }
        ++j;
    }
}

void PlayerInventoryGUI::addEquipableItem(TextureID texture, EquippedItems item) {
    Texture* currTexture = &repo.getTexture(texture);
    if(equippedTextures.count(item)){
        equippedTextures.erase(item);
    }
    equippedTextures.emplace(item, currTexture);
}

void PlayerInventoryGUI::updateGold(unsigned int gold) {
    text.updateText("GOLD: " + std::to_string(gold));
    text.render(160, 565, SDL_Color{0xFF,0xFF,0x00});
}

void PlayerInventoryGUI::_renderText() {
    text.updateText("INVENTORY");
    text.render(160, 225, SDL_Color{0xFF,0xFF,0xFF});
}
