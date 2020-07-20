//
// Created by ivan on 13/6/20.
//

#include "PlayerInventoryGUI.h"

#define INVENTORY_SIZE 16

#define INVENTORY_ITEMS_X_OFFSET 45
#define INVENTORY_ITEMS_Y_OFFSET 235

#define ITEM_WIDTH 72
#define ITEM_HEIGHT 75

#define INVENTORY_OUTLINES_X_OFFSET 73
#define INVENTORY_OUTLINES_Y_OFFSET 260

#define INVENTORY_FONT_PATH "/var/Argentum/Assets/Fonts/medieval.ttf"

PlayerInventoryGUI::PlayerInventoryGUI(TextureRepository &repo,SDL_Renderer &renderer,
                                       PlayerInfoGUI& playerInfo) :
                                       textFont(INVENTORY_FONT_PATH, 25),
                                            text(textFont,renderer), repo(repo),
                                            renderer(renderer), pInfo(playerInfo),
                                            fixedText(renderer, textFont) {
    gold = 0;
    for (int i = 0; i < INVENTORY_SIZE; ++i) {//Inicializo el vector con nullptr
        inventoryTextures.push_back(nullptr);
    }
    equippedTextures[Helmet] = nullptr;
    equippedTextures[Armor] = nullptr;
    equippedTextures[Weapon] = nullptr;
    equippedTextures[Shield] = nullptr;
}

void PlayerInventoryGUI::addInventoryItem(TextureID texture, int32_t slot) {
    if (texture == Nothing) {
        inventoryTextures[slot] = nullptr;
    } else {
        inventoryTextures[slot] = &repo.getTexture(texture);
    }
}

void PlayerInventoryGUI::addEquipableItem(TextureID texture, EquippedItems item) {
    if (texture != Nothing) {
        Texture* currTexture = &repo.getTexture(texture);
        equippedTextures.at(item) = currTexture;
    } else {
        equippedTextures.at(item) = nullptr;
    }
}

void PlayerInventoryGUI::updateGold(int32_t _gold, int32_t _safeGold) {
    gold = _gold;
    safeGold = _safeGold;
}

void PlayerInventoryGUI::render(int32_t selectedSlotX) {
    _drawInventoryOutlines(selectedSlotX);
    _drawEquipableOutlines();
    _renderInventoryItems();
    _renderEquipableItems();
    _renderText();
}

void PlayerInventoryGUI::_renderText() {
    fixedText.title.render(215, 25);
    fixedText.inventory.render(160, 225);
    pInfo.getGoldText().render(140, 565);
    pInfo.getLevelText().render(70, 50);
    _renderSkills();
    pInfo.getPositionText().render(200, 880);
    pInfo.getNicknameText().render(210,95);
}

void PlayerInventoryGUI::_renderSkills() {
    pInfo.getStrengthText().render(40, 660);
    pInfo.getConstitutionText().render(40, 700);
    pInfo.getIntelligenceText().render(40, 740);
    pInfo.getAgilityText().render(40, 780);
}

void PlayerInventoryGUI::_renderInventoryItems() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; ++j) {
            if (inventoryTextures[4*i + j] != nullptr){
                inventoryTextures[4*i + j]->render(INVENTORY_ITEMS_X_OFFSET +
                                        (ITEM_WIDTH + 6) * j,INVENTORY_ITEMS_Y_OFFSET
                                        +(i) * (ITEM_HEIGHT - 1),0);
            }
        }
    }
}

void PlayerInventoryGUI::_renderEquipableItems() {
    if (equippedTextures.at(Helmet)) {
        equippedTextures.at(Helmet)->render(250, 635,0);
    }
    if (equippedTextures.at(Armor)) {
        equippedTextures.at(Armor)->render(325, 635, 0);
    }
    if (equippedTextures.at(Weapon)) {
        equippedTextures.at(Weapon)->render(250, 735, 0);
    }
    if (equippedTextures.at(Shield)) {
        equippedTextures.at(Shield)->render(325, 735, 0);
    }
}

/* Renderiza los cuadrados en los que se divide el inventario */
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

/* Renderiza los cuadrados donde se muestran los items equipados */
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
