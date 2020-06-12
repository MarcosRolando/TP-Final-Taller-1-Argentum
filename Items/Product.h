//
// Created by agustin on 12/6/20.
//

#ifndef ARGENTUM_PRODUCT_H
#define ARGENTUM_PRODUCT_H


#include "Item.h"

struct ProductData {
    unsigned int price;
    const std::string& productName;
};

class Product {
    unsigned int price;
    std::shared_ptr<Item> item;
};


#endif //ARGENTUM_PRODUCT_H
