//
// Created by ivan on 20/6/20.
//

#ifndef ARGENTUM_SELECTOR_H
#define ARGENTUM_SELECTOR_H

#include <SDL.h>
#include "../Screen/Window.h"
#include "../Map/Coordinate.h"
#include "../Shared/GameEnums.h"

//Maneja las cosas que selecciona el usuario
class Selector {
private:
    //Coordinate clickX;
    Coordinate inventorySlot;
    Coordinate selectedTile;
    GameType::EquipmentPlace selectedEquipment;

public:
    Selector();
    //Se fija si el click fue en el mapa o en el inventario. Dependiendo el caso
    //Guarda el tile/inventorySlot que se haya seleccionado. todo ver offset de la camara
    void handleEvent(Coordinate click, Coordinate playerPos, Window& window);
    //Devuelve el inventorySlot actualmente seleccionado
    int getInventorySlot() const;
    //Devuelve la coordenada del tile actualmente seleccionado
    Coordinate getSelectedTile() const;
    //Para debuggin. Me devuelve el tile relativo para renderizar el outline
    Coordinate getSelectedTileToRender(Coordinate playerPos) const;
    //Me devuelve el item equipado que seleccione
    GameType::EquipmentPlace getSelectedEquipment() const;
    //Devuelve true si seleccione un tile
    bool hasSelectedTile(Coordinate click) const;
    //Devuelve true si seleccione un slot
    bool hasSelectedSlot(Coordinate click) const;
    //Devuelve true si seleccione un item de equipables
    bool hasSelectedEquipment(Coordinate click) const;
    //setea el tile seleccionado a {-1,-1}
    void resetTileSelection();
    ~Selector();

private:
    void _verifyTileSelection(Coordinate playerPos, Coordinate click);
    void _verifyInventorySlotSelection(Coordinate click);
    bool _isInsideRect(Coordinate click, int left, int right, int top,
            int bottom) const;
    void _verifySelectedEquipment(Coordinate click);


};


#endif //ARGENTUM_SELECTOR_H
