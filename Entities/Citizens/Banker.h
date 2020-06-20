//
// Created by agustin on 15/6/20.
//

#ifndef ARGENTUM_BANKER_H
#define ARGENTUM_BANKER_H

#include <unordered_map>
#include "../Entity.h"

class Storage;

//Clase que se encarga de guardar todos los items que le otorgue el jugador
//El jugador puede darle oro o items nuevos para que guarde o sacar oro o items
class Banker : Entity {
private:
    //Storage storage;
    static std::unordered_map<std::string, Storage> playersStorages;

public:
    explicit Banker(Coordinate initialPosition);

    //Almacena una lista con los datos de los items y oro almacenados
    //NO TIENE QUE ALMACENAR PRODUCTDATA, CAMBIAR
    unsigned int list(const Player &player, std::list<ProductData>& products) override;

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


    //Recibe los items de un player y su nickname, y los agrega a lo que tiene guardado
    //HACER QUE RECIBA PARAMETROS COMO LOS DE STORAGE, PORQUE SE VA A CONSTRUIR UN STORAGE
    //EN EL NICKNAME RECIBIDO
    static void addPlayerItems(const std::string& playerName, const std::unordered_map<std::string, unsigned int>&
                               initialItemsAmounts, unsigned int gold);
};


#endif //ARGENTUM_BANKER_H
