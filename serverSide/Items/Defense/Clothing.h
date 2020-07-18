//
// Created by agustin on 9/6/20.
//

#ifndef ARGENTUM_CLOTHING_H
#define ARGENTUM_CLOTHING_H

#include "../Item.h"
#include "../../Config/Configuration.h"

class ItemTests;

/*Esta clase encapsula el comportamiento general de la ropa*/

class Clothing : public Item {
private:
    unsigned int minDefense;
    unsigned int maxDefense;

    friend ItemTests;

public:
    explicit Clothing(GameType::Clothing clothing);

    /*Retorna un random entre la minima y maxima defensa del item*/
    unsigned int getDefense() const;

    /*Esta funcion existe para que cuando el player muera y tire todos sus items
    sepa reconocer los default y no los tire*/
    virtual bool isDefault() const = 0;

    virtual ~Clothing() = default;
};


#endif //ARGENTUM_CLOTHING_H
