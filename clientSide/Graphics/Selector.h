//
// Created by ivan on 20/6/20.
//

#ifndef ARGENTUM_SELECTOR_H
#define ARGENTUM_SELECTOR_H

#include <SDL.h>
#include "../Screen/Window.h"
#include "../Map/Coordinate.h"
#include "../../libs/GameEnums.h"
#include <mutex>

//Maneja las cosas que selecciona el usuario
class Selector {
private:
    //Coordinate clickX;
    Coordinate inventorySlot;
    Coordinate selectedTile;
    GameType::EquipmentPlace selectedEquipment;
    std::mutex m;

public:
    Selector();

    //Se fija si el click fue en el mapa o en el inventario. Dependiendo el caso
    //Guarda el tile/inventorySlot/equipable que se haya seleccionado.
    void handleEvent(Coordinate click, Coordinate playerPos, Window& window);

    //Devuelve el inventorySlot actualmente seleccionado
    int getInventorySlot();

    //Devuelve la coordenada del tile actualmente seleccionado
    Coordinate getSelectedTile();

    //Me devuelve el item equipado que seleccione
    GameType::EquipmentPlace getSelectedEquipment();

    //Devuelve true si seleccione un tile
    static bool hasSelectedTile(Coordinate click);

    //Devuelve true si seleccione un slot del inventario
    static bool hasSelectedSlot(Coordinate click);

    //Devuelve true si seleccione un item equipado
    static bool hasSelectedEquipment(Coordinate click);

    //Setea el tile seleccionado a (0,0)
    void resetTileSelection();

    ~Selector();

private:
    void _verifyTileSelection(Coordinate playerPos, Coordinate click);
    void _verifyInventorySlotSelection(Coordinate click);
    static bool _isInsideRect(Coordinate click, int left, int right, int top,
            int bottom) ;
    void _verifySelectedEquipment(Coordinate click);


};


#endif //ARGENTUM_SELECTOR_H
