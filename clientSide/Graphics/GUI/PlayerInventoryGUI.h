//
// Created by ivan on 13/6/20.
//

#ifndef ARGENTUM_PLAYERINVENTORYGUI_H
#define ARGENTUM_PLAYERINVENTORYGUI_H

#include "../../Texture/TextureRepository.h"
#include "../Text/Text.h"
#include "PlayerInfoGUI.h"
#include <list>
#include <unordered_map>

class PlayerInventoryGUI {
private:
    Font textFont;
    Text text;
    TextureRepository& repo;
    SDL_Renderer& renderer;
    std::vector<Texture*> inventoryTextures;
    std::unordered_map<EquippedItems, Texture*> equippedTextures;
    PlayerInfoGUI& pInfo;
    int32_t gold, safeGold;

public:
    /* Constructor */
    PlayerInventoryGUI(TextureRepository& repo, SDL_Renderer& renderer, PlayerInfoGUI& playerInfo);
    /* Agrega la textura del item al slot correspondiente */
    void addInventoryItem(TextureID texture, int32_t slot);
    /* Agrega un item a la posicion correspondiente de los equipables */
    void addEquipableItem(TextureID texture, EquippedItems item);
    /* Actualiza la cantidad de oro y oro seguro */
    void updateGold(int32_t gold, int32_t _safeGold);
    /* Renderiza el inventario y la informacion del jugador */
    void render(int32_t selectedSlot);

private:
    void _drawInventoryOutlines(int32_t x);
    void _renderInventoryItems();
    void _drawEquipableOutlines();
    void _renderEquipableItems();
    void _renderText();
    void _renderSkills();
};


#endif //ARGENTUM_PLAYERINVENTORYGUI_H
