//
// Created by ivan on 20/6/20.
//

#include "../Client/GameConstants.h"
#include "Selector.h"
#include <iostream>

#define DEFAULT_MAP_LEFT 20
#define DEFAULT_MAP_RIGHT 1044
#define DEFAULT_MAP_TOP 236
#define DEFAULT_MAP_BOTTOM 876

#define CAMERA_X_OFFSET 27
#define CAMERA_Y_OFFSET 15

#define DEFAULT_INVENTORY_LEFT 1122
#define DEFAULT_INVENTORY_RIGHT 1434
#define DEFAULT_INVENTORY_TOP 260
#define DEFAULT_INVENTORY_BOTTOM 548

#define INVENTORY_SLOT_WIDTH 78
#define INVENTORY_SLOT_HEIGHT 72



Selector::Selector() {
    inventorySlot = {0, 0};
    selectedTile = {0, 0};
}

void Selector::handleEvent(Coordinate click, Coordinate playerPos, Window& window){
    _verifyTileSelection(playerPos, click);
    _verifyInventorySlotSelection(click);
    _verifySelectedEquipment(click);
}

void Selector::_verifyTileSelection(Coordinate playerPos, Coordinate click) {
    std::lock_guard<std::mutex> l(m);
    //Veo si clickeo adentro del mapa
    if (_isInsideRect(click, DEFAULT_MAP_LEFT, DEFAULT_MAP_RIGHT, DEFAULT_MAP_TOP,
            DEFAULT_MAP_BOTTOM)){
        //Esto es cuando no esta en los extremos
        int playerXTile = playerPos.j;
        int playerYTile = playerPos.i;
        int relativeXTile = (click.j - DEFAULT_MAP_LEFT + CAMERA_X_OFFSET) / TILE_WIDTH;
        int relativeYTile = (click.i - DEFAULT_MAP_TOP - CAMERA_Y_OFFSET) / TILE_HEIGHT;
        selectedTile.j = playerXTile + (relativeXTile - 4);
        selectedTile.i = playerYTile + (relativeYTile - 2);

        //Me fijo los extremos
        if (playerXTile < 4){
            selectedTile.j = (click.j - DEFAULT_MAP_LEFT) / TILE_WIDTH;
        } else if (playerXTile > 95){
            selectedTile.j = 92 + ((click.j - DEFAULT_MAP_LEFT) / TILE_WIDTH);
        }
        if (playerYTile < 3){
            selectedTile.i = (click.i - DEFAULT_MAP_TOP) / TILE_HEIGHT;
        }else if (playerYTile > 97){
            selectedTile.i = 95 + ((click.i - DEFAULT_MAP_TOP) / TILE_HEIGHT);
        }
    }
}

void Selector::_verifyInventorySlotSelection(Coordinate click) {
    std::lock_guard<std::mutex> l(m);
    //Veo si clickeo adentro del inventario
    if (_isInsideRect(click, DEFAULT_INVENTORY_LEFT, DEFAULT_INVENTORY_RIGHT,
            DEFAULT_INVENTORY_TOP, DEFAULT_INVENTORY_BOTTOM)){
        inventorySlot.j = (click.j - DEFAULT_INVENTORY_LEFT) / INVENTORY_SLOT_WIDTH;
        inventorySlot.i = (click.i - DEFAULT_INVENTORY_TOP) / INVENTORY_SLOT_HEIGHT;
    }
}

void Selector::_verifySelectedEquipment(Coordinate click) {
    std::lock_guard<std::mutex> l(m);
    if (_isInsideRect(click, 1320, 1392, 660, 735)){//Casco
        selectedEquipment = GameType::EQUIPMENT_PLACE_HEAD;
    } else if (_isInsideRect(click, 1397, 1469, 660, 735)){//Chest
        selectedEquipment = GameType::EQUIPMENT_PLACE_CHEST;
    } else if (_isInsideRect(click, 1320, 1392, 760, 835)){//Weapon
        selectedEquipment = GameType::EQUIPMENT_PLACE_WEAPON;
    } else if (_isInsideRect(click, 1397, 1469, 760, 835)){//Shield
        selectedEquipment = GameType::EQUIPMENT_PLACE_SHIELD;
    }
}

bool Selector::hasSelectedTile(Coordinate click) {
    return _isInsideRect(click, DEFAULT_MAP_LEFT, DEFAULT_MAP_RIGHT, DEFAULT_MAP_TOP,
                         DEFAULT_MAP_BOTTOM);
}

bool Selector::hasSelectedSlot(Coordinate click) {
    return _isInsideRect(click, DEFAULT_INVENTORY_LEFT, DEFAULT_INVENTORY_RIGHT,
                         DEFAULT_INVENTORY_TOP, DEFAULT_INVENTORY_BOTTOM);
}

bool Selector::hasSelectedEquipment(Coordinate click) {
    //Aca me fijo si esta entre los 4 cuadrados de equipamiento
    return _isInsideRect(click, 1320, 1469,
                         660, 835);
}

int Selector::getInventorySlot() {
    std::lock_guard<std::mutex> l(m);
    return inventorySlot.j + (4 * inventorySlot.i);
}

Coordinate Selector::getSelectedTile() {
    std::lock_guard<std::mutex> l(m);
    return {selectedTile.i, selectedTile.j};
}

GameType::EquipmentPlace Selector::getSelectedEquipment() {
    std::lock_guard<std::mutex> l(m);
    return selectedEquipment;
}

void Selector::resetTileSelection() {
    std::lock_guard<std::mutex> l(m);
    selectedTile = {0, 0};
}

bool Selector::_isInsideRect(Coordinate click, int left, int right, int top, int bottom) {
    return (click.j > left && click.j < right && click.i > top && click.i < bottom);
}


Selector::~Selector() = default;