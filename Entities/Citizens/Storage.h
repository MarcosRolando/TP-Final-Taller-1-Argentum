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
#include "../../Items/Item.h"

//Clase utilizada para guardar instancias de items, se guardan las instancias
//y no cantidades de cada item ya que de esa forma no se debe estar creando y
//copiando cada vez que se retira algun item. Esto permite ademas extensibilidad
//ya que se podria agregar a cada item por separado modificadores y estos quedarian
//guardados en la instancia

//Cualquier tipo de item que sea guardado 0 veces no tiene un lugar en el unordered_map

struct ProductData {
    const std::string& name;
    unsigned int stock; //Cantidad de instancias del item de nombre name guardadas
    unsigned int price; //Precio de venta del item

    ProductData(const std::string& _name, unsigned int _stock, unsigned int _price): name(_name) {
        stock = _stock;
        price = _price;
    }
};

//Esta clase se encarga de manejar el stock de items, los guarda y maneja
//su agregado y retiro
class Storage {
private:
    unsigned int storedGold;
    std::unordered_map<std::string, std::list<std::shared_ptr<Item>>> storedItems;
public:

    //Se apropia de los contenidos de initialProducts
    explicit Storage(const std::unordered_map<std::string, unsigned int>&
                     initialItemsAmmounts, unsigned int initialGold);

    //Almacena el item, apropiandose de el
    void storeItem(std::shared_ptr<Item>&& item);

    //Intenta pasar el item pedido de Storage a Player, si el item no existe o
    //el player no tiene espacio entonces no hace nada
    void retreiveItem(const std::string& itemName, Player& player);

    //Almacena en la lista instancias del struct ProductData, retorna la cantidad
    //de oro que tiene almacenada storage
    //Multiplica el precio del item por priceMultiplier
    unsigned int getStorageData(std::list<ProductData>& products,
                                   float priceMultiplier) const;

    //Indica si el item con el nombre indicado se encuentra guardado
    bool isItemAvailable(const std::string& itemName) const;

    //Retorna el precio base del producto con el nombre recibido, si el nombre
    //es invalido se tira out_of_range
    unsigned int getItemPrice(const std::string& itemName) const;

    void increaseGoldReserves(unsigned int amount);

    bool decreaseGoldReserves(unsigned int amount);
};


#endif //ARGENTUM_STORAGE_H
