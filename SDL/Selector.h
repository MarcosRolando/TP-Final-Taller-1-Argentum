//
// Created by ivan on 20/6/20.
//

#ifndef ARGENTUM_SELECTOR_H
#define ARGENTUM_SELECTOR_H

//Maneja las cosas que selecciona el usuario
class Selector {
private:
    int inventorySlotX, inventorySlotY;
    int tileX, tileY;
public:
    Selector();
    void verifyTileSelection(int xClick, int yClick, int playerX, int playerY);
    void verifyInventorySlotSelection(int clickX, int clickY);
    int getInventorySlotX() const;
    int getInventorySlotY() const;
    int getSelectedTileX() const;
    int getSelectedTileY() const;
    int getSelectedTileXToRender(int xPlayer) const;//Estas son para debugging, despues
    // vemos si las dejamos para el juego
    int getSelectedTileYToRender(int yPlayer) const;

    ~Selector();
};


#endif //ARGENTUM_SELECTOR_H
