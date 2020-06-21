//
// Created by ivan on 20/6/20.
//

#include "../GameConstants.h"
#include "Selector.h"

#define DEFAULT_MAP_LEFT 20
#define DEFAULT_MAP_RIGHT 1044
#define DEFAULT_MAP_TOP 236
#define DEFAULT_MAP_BOTTOM 876

Selector::Selector() {
    inventorySlotX = -1;
    inventorySlotY = -1;
    tileX = -1;
    tileY = -1;
}

Selector::~Selector() {

}

void Selector::handleEvent(SDL_Event &e,int playerX, int playerY, Window& window){
    if( e.type == SDL_MOUSEBUTTONDOWN )
    {
        int windowWidth = window.getWidth();
        int windowHeight = window.getHeight();
        SDL_GetMouseState(&clickX, &clickY);
        //Escalo la posicion de click
        clickX = (float)clickX * ((float)DEFAULT_SCREEN_WIDTH/(float)
                windowWidth);
        clickY = (float)clickY * ((float)DEFAULT_SCREEN_HEIGHT/(float)
                windowHeight);

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
        int relativeXTile = (clickX - 20 + 50) / TILE_WIDTH;//El -20
        // es el offset del marco. EL -50 es el offset de la camara
        int relativeYTile = (clickY - 236 - 12) / TILE_HEIGHT;//El -236 es
        //el offset del minichat. El -12 es el offset de la camara
        tileX = playerXTile + (relativeXTile - 4);
        tileY = playerYTile + (relativeYTile - 2);

        //Me fijo los extremos
        if (playerXTile < 4){
            tileX = (clickX - 20) / TILE_WIDTH;
        }
        if (playerXTile > 95){
            tileX = 92 + ((clickX - 20) / TILE_WIDTH);
        }
        if (playerYTile < 2){
            tileY = (clickY - 236) / TILE_HEIGHT;
        }
        if (playerYTile > 97){
            tileY = 95 + ((clickY - 236) / TILE_HEIGHT);
        }

    }
}

void Selector::_verifyInventorySlotSelection() {
    //Veo si clickeo adentro del inventario
    if (clickX > 1122 && clickX < 1434 && clickY > 260 && clickY < 548){
        inventorySlotX = (clickX-1122)/78;//78=slot width
        inventorySlotY = (clickY-260)/72;//72=slot height
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
        cameraOffset = 50;
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
        cameraOffset = 12;
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
