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


PlayerInventoryGUI::PlayerInventoryGUI(TextureRepository &repo,SDL_Renderer &renderer,
                                       PlayerInfoGUI& playerInfo) :
                                       textFont("../SDL/Text/medieval.ttf", 25),
                                            text(textFont,renderer), repo(repo),
                                            renderer(renderer), pInfo(playerInfo) {
    gold = 0;
    for (int i = 0; i < INVENTORY_SIZE; ++i) {//Inicializo el vector con nullptr
        inventoryTextures.push_back(nullptr);
    }
}

void PlayerInventoryGUI::addInventoryItem(TextureID texture, int32_t slot) {
    inventoryTextures[slot] = &repo.getTexture(texture);
}

void PlayerInventoryGUI::removeInventoryItem(int32_t inventorySlot) {
    inventoryTextures.erase(inventoryTextures.begin() + inventorySlot);//Ver si esto funciona
}

void PlayerInventoryGUI::addEquipableItem(TextureID texture, EquippedItems item) {
    if (texture != Nothing){
        Texture* currTexture = &repo.getTexture(texture);
        if (equippedTextures.count(item)) {
            equippedTextures.erase(item);
        }
        equippedTextures.emplace(item, currTexture);
    }
}

void PlayerInventoryGUI::updateGold(int32_t _gold) {
    gold = _gold;
}

void PlayerInventoryGUI::render(int32_t selectedSlotX) {
    _drawInventoryOutlines(selectedSlotX);
    _drawEquipableOutlines();
    _renderInventoryItems();
    _renderEquipableItems();
    _renderText();
}

void PlayerInventoryGUI::_renderText() {
    text.updateText("INVENTORY");
    text.render(160, 225, SDL_Color{0xFF,0xFF,0xFF});

    text.updateText("GOLD: " + std::to_string(gold));
    text.render(160, 565, SDL_Color{0xFF,0xFF,0x00});

    text.updateText(std::to_string(pInfo.getLevel()));
    text.render(70, 50, SDL_Color{0xFF,0xFF,0xFF});

    _renderSkills();

    text.updateText("X: " + std::to_string(pInfo.getXPos()) + "   " + "Y: " +
                    std::to_string(pInfo.getYPos()));
    text.render(200, 880, {0xFF, 0xFF, 0xFF});
}

void PlayerInventoryGUI::_renderSkills(){
    text.updateText("STRENGTH : " + std::to_string(pInfo.getStrength()));
    text.render(40, 660, SDL_Color{0xFF,0xFF,0xFF});

    text.updateText("CONSTITUTION : " + std::to_string(pInfo.getConstitution()));
    text.render(40, 700, SDL_Color{0xFF,0xFF,0xFF});

    text.updateText("INTELLIGENCE : " + std::to_string(pInfo.getIntelligence()));
    text.render(40, 740, SDL_Color{0xFF,0xFF,0xFF});

    text.updateText("AGILITY : " + std::to_string(pInfo.getAgility()));
    text.render(40, 780, SDL_Color{0xFF,0xFF,0xFF});
}

void PlayerInventoryGUI::_renderInventoryItems() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; ++j) {
            if (inventoryTextures[4*i + j] != nullptr){
                inventoryTextures[4*i + j]->render(INVENTORY_ITEMS_X_OFFSET +
                                        (ITEM_WIDTH + 6) * j,INVENTORY_ITEMS_Y_OFFSET
                                        +(i/LINES) * (ITEM_HEIGHT - 1),0);
            }
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

void PlayerInventoryGUI::_drawInventoryOutlines(int32_t selectedSlot) {
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
