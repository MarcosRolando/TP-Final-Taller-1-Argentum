//
// Created by agustin on 15/6/20.
//

#ifndef ARGENTUM_BANKER_H
#define ARGENTUM_BANKER_H


#include "../Entity.h"

class Banker: Entity {
private:
    Storage storage;

public:
    //Almacena una lista con los datos de los items y oro almacenados
    //NO TIENE QUE ALMACENAR PRODUCTDATA, CAMBIAR
    void list(std::list<ProductData>& products) override;

    //Intenta sacar el item del banco y almacenarlo en el inventario del jugador
    //Si el item no esta guardado en el banco o el judador no tiene espacio en
    //su inventario entonces no hace nada
    //Si se intenta sacar mas oro del guardado, entonces saca el oro disponible
    //Si se quiere sacar oro se debe poner en itemName "oro <cantidad>" sin incluir
    //los <>
    void withdraw(Player& player, const std::string& itemName) override;

    //Intenta guardar el item en el banco, sacandolo del inventario del jugador
    //Si el item no esta en el inventario del judador entonces no hace nada
    //No se pueden guardar items equipados
    //Si se intenta depositar mas oro del guardado, entonces deposita la totalidad del oro
    //Si se quiere depositar oro se debe poner en itemName "oro <cantidad>" sin incluir
    //los <>
    void deposit(Player& player, const std::string& itemName) override;
};


#endif //ARGENTUM_BANKER_H
