//
// Created by agustin on 15/6/20.
//

#ifndef ARGENTUM_STORAGE_H
#define ARGENTUM_STORAGE_H

#include <string>
#include <unordered_map>
#include <list>
#include <utility>
#include <memory>
#include "Item.h"

//Clase utilizada para guardar instancias de items, se guardan las instancias
//y no cantidades de cada item ya que de esa forma no se debe estar creando y
//copiando cada vez que se retira algun item. Esto permite ademas extensibilidad
//ya que se podria agregar a cada item por separado modificadores y estos quedarian
//guardados en la instancia

//Cualquier tipo de item que sea guardado 0 veces no tiene un lugar en el unordered_map

struct ProductData {
    std::string name;
    unsigned int price;
    unsigned int stock;
};

class Storage {
private:
    std::unordered_map<std::string, std::list<std::shared_ptr<Item>>> storedItems;
public:
    //Se apropia de los contenidos de initialProducts
    explicit Storage(std::unordered_map<std::string,
                     std::list<std::shared_ptr<Item>>>&& initialItems) noexcept;

    //Almacena el item, apropiandose de el
    void storeItem(std::shared_ptr<Item>&& item);

    //Intenta pasar el item pedido de Storage a Player, si el item no existe o
    //el player no tiene espacio retorna false, sino retorna false y storage no
    //es modificado
    bool retreiveItem(std::string itemName, Player& player);
};


#endif //ARGENTUM_STORAGE_H
