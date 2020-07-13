//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_PRODUCTDATA_H
#define ARGENTUM_PRODUCTDATA_H

struct ProductData {
    const std::string& name;
    unsigned int stock; //Cantidad de instancias del item de nombre name guardadas
    unsigned int price; //Precio de venta del item

    ProductData(const std::string& _name, unsigned int _stock, unsigned int _price): name(_name) {
        stock = _stock;
        price = _price;
    }
};

#endif //ARGENTUM_PRODUCTDATA_H
