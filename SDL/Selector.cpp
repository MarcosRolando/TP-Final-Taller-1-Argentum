//
// Created by ivan on 20/6/20.
//

#include "../GameConstants.h"
#include "Selector.h"

#define DEFAULT_MAP_LEFT 20
#define DEFAULT_MAP_RIGHT 1044
#define DEFAULT_MAP_TOP 236
#define DEFAULT_MAP_BOTTOM 876

#define CAMERA_X_OFFSET 50
#define CAMERA_Y_OFFSET 12

#define DEFAULT_INVENTORY_LEFT 1122
#define DEFAULT_INVENTORY_RIGHT 1434
#define DEFAULT_INVENTORY_TOP 260
#define DEFAULT_INVENTORY_BOTTOM 548

#define INVENTORY_SLOT_WIDTH 78
#define INVENTORY_SLOT_HEIGHT 72



Selector::Selector() {
    inventorySlotX = -1;
    inventorySlotY = -1;
    tileX = -1;
    tileY = -1;
}

void Selector::handleEvent(SDL_Event &e,int playerX, int playerY, Window& window){
    if( e.type == SDL_MOUSEBUTTONDOWN )
    {
        SDL_GetMouseState(&clickX, &clickY);
        //Escalo la posicion de click
        clickX = (float)clickX *
                ((float)DEFAULT_SCREEN_WIDTH/(float)window.getWidth());
        clickY = (float)clickY *
                ((float)DEFAULT_SCREEN_HEIGHT/(float)window.getHeight());

        _verifyTileSelection(playerX, playerY);
        _verifyInventorySlotSelection();
    }
}

void Selector::_verifyTileSelection(int playerX, int playerY) {
    //Veo si clickeo adentro del mapa
    if (_isInsideRect(DEFAULT_MAP_LEFT, DEFAULT_MAP_RIGHT, DEFAULT_MAP_TOP, DEFAULT_MAP_BOTTOM)){
        //Esto es cuando no esta en los extremos
        int playerXTile = playerX/TILE_WIDTH;
        int playerYTile = playerY/TILE_HEIGHT;
        int relativeXTile = (clickX - DEFAULT_MAP_LEFT + CAMERA_X_OFFSET) / TILE_WIDTH;
        int relativeYTile = (clickY - DEFAULT_MAP_TOP - CAMERA_Y_OFFSET) /TILE_HEIGHT;
        tileX = playerXTile + (relativeXTile - 4);
        tileY = playerYTile + (relativeYTile - 2);

        //Me fijo los extremos
        //Izquierda
        if (playerXTile < 4){
            tileX = (clickX - DEFAULT_MAP_LEFT) / TILE_WIDTH;
        } else if (playerXTile > 95){
            tileX = 92 + ((clickX - DEFAULT_MAP_LEFT) / TILE_WIDTH);
        }
        if (playerYTile < 3){
            tileY = (clickY - DEFAULT_MAP_TOP) / TILE_HEIGHT;
        }else if (playerYTile > 97){
            tileY = 95 + ((clickY - DEFAULT_MAP_TOP) / TILE_HEIGHT);
        }

    }
}

void Selector::_verifyInventorySlotSelection() {
    //Veo si clickeo adentro del inventario
    if (_isInsideRect(DEFAULT_INVENTORY_LEFT, DEFAULT_INVENTORY_RIGHT,
            DEFAULT_INVENTORY_TOP, DEFAULT_INVENTORY_BOTTOM)){
        inventorySlotX = (clickX - DEFAULT_INVENTORY_LEFT)/INVENTORY_SLOT_WIDTH;
        inventorySlotY = (clickY - DEFAULT_INVENTORY_TOP)/INVENTORY_SLOT_HEIGHT;
    }
}

int Selector::getInventorySlotX() const {
    return inventorySlotX;
}


int Selector::getInventorySlotY() const {
    return inventorySlotY;
}

int Selector::getSelectedTileX() const {
    return tileX;
}


int Selector::getSelectedTileY() const {
    return tileY;
}

int Selector::getSelectedTileXToRender(int xPlayer) const {
    int playerXTile = xPlayer/TILE_WIDTH;
    int cameraOffset = 0,tileXOffset = 0;
    if (playerXTile > 3 && playerXTile < 96){
        cameraOffset = CAMERA_X_OFFSET;
        tileXOffset = -playerXTile + 4;
    }
    if (playerXTile > 95){
        tileXOffset = -92;
    }
    return (tileX + tileXOffset) * 128 - cameraOffset;
}

int Selector::getSelectedTileYToRender(int yPlayer) const {
    int playerYTile = yPlayer/TILE_WIDTH;
    int cameraOffset = 0, tileYOffset = 0;
    if (playerYTile > 2 && playerYTile < 98){
        cameraOffset = CAMERA_Y_OFFSET;
        tileYOffset = -(yPlayer / TILE_HEIGHT) + 2;
    }
    if (playerYTile >= 98){
        tileYOffset = -95;
    }
    return (tileY + tileYOffset) * 128 + cameraOffset;
}

bool Selector::_isInsideRect(int left, int right, int top, int bottom) const{
    return (clickX > left && clickX < right && clickY > top && clickY < bottom);
}


Selector::~Selector() {}