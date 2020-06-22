//
// Created by ivan on 20/6/20.
//

#ifndef ARGENTUM_SELECTOR_H
#define ARGENTUM_SELECTOR_H

#include <SDL.h>
#include "../Screen/Window.h"

//Maneja las cosas que selecciona el usuario
class Selector {
private:
    int clickX, clickY;
    int inventorySlotX, inventorySlotY;
    int tileX, tileY;
public:
    Selector();
    void handleEvent(SDL_Event &e, int playerX, int playerY, Window& window);
    int getInventorySlot() const;
    int getSelectedTileX() const;
    int getSelectedTileY() const;
    int getSelectedTileXToRender(int xPlayer) const;//Estas son para debugging, despues
    // vemos si las dejamos para el juego
    int getSelectedTileYToRender(int yPlayer) const;
    ~Selector();

private:
    void _verifyTileSelection(int playerX, int playerY);
    void _verifyInventorySlotSelection();
    bool _isInsideRect(int left, int right, int top, int bottom) const;
};


#endif //ARGENTUM_SELECTOR_H
