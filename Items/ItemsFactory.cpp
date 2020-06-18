//
// Created by agustin on 16/6/20.
//

#include "ItemsFactory.h"

ItemsFactory &ItemsFactory::getInstance() {
    static ItemsFactory factory;
    return factory;
}
