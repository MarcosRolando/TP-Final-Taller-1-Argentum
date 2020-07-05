//
// Created by ivan on 20/6/20.
//

#include "../GameConstants.h"
#include "Selector.h"

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
    inventorySlot = {-1, -1};
    selectedTile = {-1, -1};
    tileSelected = false;
    slotSelected = false;
    //click = {-1, -1};
}

void Selector::handleEvent(Coordinate click, Coordinate playerPos, Window& window){
    _verifyTileSelection(playerPos, click);
    _verifyInventorySlotSelection(click);
}

void Selector::_verifyTileSelection(Coordinate playerPos, Coordinate click) {
    //Veo si clickeo adentro del mapa
    if (_isInsideRect(click, DEFAULT_MAP_LEFT, DEFAULT_MAP_RIGHT, DEFAULT_MAP_TOP,
            DEFAULT_MAP_BOTTOM)){
        tileSelected = true;
        slotSelected = false;
        //Esto es cuando no esta en los extremos
        int playerXTile = playerPos.j;///TILE_WIDTH;
        int playerYTile = playerPos.i;///TILE_HEIGHT;
        int relativeXTile = (click.j - DEFAULT_MAP_LEFT + CAMERA_X_OFFSET) / TILE_WIDTH;
        int relativeYTile = (click.i - DEFAULT_MAP_TOP - CAMERA_Y_OFFSET) / TILE_HEIGHT;
        selectedTile.j = playerXTile + (relativeXTile - 4);
        selectedTile.i = playerYTile + (relativeYTile - 2);

        //Me fijo los extremos
        //Izquierda
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
    //Veo si clickeo adentro del inventario
    if (_isInsideRect(click, DEFAULT_INVENTORY_LEFT, DEFAULT_INVENTORY_RIGHT,
            DEFAULT_INVENTORY_TOP, DEFAULT_INVENTORY_BOTTOM)){
        tileSelected = false;
        slotSelected = true;
        inventorySlot.j = (click.j - DEFAULT_INVENTORY_LEFT)/INVENTORY_SLOT_WIDTH;
        inventorySlot.i = (click.i - DEFAULT_INVENTORY_TOP)/INVENTORY_SLOT_HEIGHT;
    }
}

bool Selector::hasSelectedTile(Coordinate click) const {
    return _isInsideRect(click, DEFAULT_MAP_LEFT, DEFAULT_MAP_RIGHT, DEFAULT_MAP_TOP,
                         DEFAULT_MAP_BOTTOM);
}

bool Selector::hasSelectedSlot(Coordinate click) const {
    return _isInsideRect(click, DEFAULT_INVENTORY_LEFT, DEFAULT_INVENTORY_RIGHT,
                         DEFAULT_INVENTORY_TOP, DEFAULT_INVENTORY_BOTTOM);
}

int Selector::getInventorySlot() const {
    return inventorySlot.j + (4 * inventorySlot.i);
}

Coordinate Selector::getSelectedTile() const {
    return {selectedTile.i, selectedTile.j};
}

Coordinate Selector::getSelectedTileToRender(Coordinate playerPos) const {
    int playerYTile = playerPos.i;;
    int playerXTile = playerPos.j;
    int cameraYOffset = 0, tileYOffset = 0;
    int cameraXOffset = 0,tileXOffset = 0;
    if (playerYTile > 2 && playerYTile < 98){
        cameraYOffset = CAMERA_Y_OFFSET;
        tileYOffset = -playerYTile + 2;
    }
    if (playerYTile >= 98){
        tileYOffset = -95;
    }
    if (playerXTile > 3 && playerXTile < 96){
        cameraXOffset = CAMERA_X_OFFSET;
        tileXOffset = -playerXTile + 4;
    }
    if (playerXTile > 95){
        tileXOffset = -92;
    }
    //Ver bien el orden, capaz me maree con el ij/xy
    return {(selectedTile.i + tileYOffset) * 128 + cameraYOffset,
            (selectedTile.j + tileXOffset) * 128 - cameraXOffset};
}

bool Selector::_isInsideRect(Coordinate click, int left, int right, int top, int bottom) const{
    return (click.j > left && click.j < right && click.i > top && click.i < bottom);
}


Selector::~Selector() {}