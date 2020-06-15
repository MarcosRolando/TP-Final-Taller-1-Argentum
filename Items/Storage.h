//
// Created by agustin on 15/6/20.
//

#ifndef ARGENTUM_STORAGE_H
#define ARGENTUM_STORAGE_H

#include <string>
#include <unordered_map>
#include <list>
#include <utility>
#include "Item.h"

//Clase utilizada para guardar instancias de items, se guardan las instancias
//y no cantidades de cada item ya que de esa forma no se debe estar creando y
//copiando cada vez que se retira algun item. Esto permite ademas extensibilidad
//ya que se podria agregar a cada item por separado modificadores y estos quedarian
//guardados en la instancia
class Storage {
private:
    std::unordered_map<std::string, std::list<Item>> storedItems;
public:
    //Se apropia de los contenidos de initialProducts
    explicit Storage(std::unordered_map<std::string, std::list<Item>>&& initialItems) noexcept;
};


#endif //ARGENTUM_STORAGE_H
