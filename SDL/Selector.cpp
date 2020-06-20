//
// Created by ivan on 20/6/20.
//

#include "../GameConstants.h"
#include "Selector.h"
#include<iostream>

Selector::Selector() {
    inventorySlotX = -1;
    inventorySlotY = -1;
    tileX = -1;
    tileY = -1;
}

Selector::~Selector() {

}

void Selector::verifyTileSelection(int xClick, int yClick, int playerX,
                                   int playerY) {
    //Veo si clickeo adentro del mapa
    if (xClick>20 && xClick<1044 && yClick>236 && yClick < 876){
        tileX = (xClick - 20) / TILE_WIDTH;
        tileY = (yClick - 236) / TILE_HEIGHT;

        //Me fijo si esta en los extremos del mapa y por lo tanto su hay un
        // desfase de la camara
        int playerXTile = playerX/TILE_WIDTH;
        int playerYTile = playerY/TILE_HEIGHT;
        if ((playerXTile > 3 && playerXTile < 96)) {
            //El -20 es por el marco del mapa. El 50 es para el
            // desfase de la camara.
            int relativeXTile = (xClick - 20 + 50) / TILE_WIDTH;
            tileX = playerXTile + (relativeXTile - 4);
        }
        if ((playerYTile > 1 && playerYTile < 98)){
            int relativeYTile = (yClick - 236) / TILE_HEIGHT;//El -236 es por el minichat
            tileY = playerYTile + (relativeYTile - 2);
        }
    }
}

void Selector::verifyInventorySlotSelection(int clickX, int clickY) {
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


