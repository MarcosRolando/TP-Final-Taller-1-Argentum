//
// Created by agustin on 9/6/20.
//

#ifndef ARGENTUM_CLOTHING_H
#define ARGENTUM_CLOTHING_H

#include "../Item.h"
#include "../../Config/Configuration.h"

class Clothing : public Item {
private:
    unsigned int minDefense;
    unsigned int maxDefense;
public:
    //explicit Clothing(unsigned int minDefense, unsigned int maxDefense, std::string name);
    //explicit Clothing(const Config::ClothingData& stats);
    explicit Clothing(GameType::Clothing clothing);

    unsigned int getDefense();

    //Esta funcion existe para que cuando el player muera y tire todos sus items
    //sepa reconocer los default y no los tire
    virtual bool isDefault();

    //virtual EquipmentPlace use(Player& player) = 0;
    virtual ~Clothing() = default;
};


#endif //ARGENTUM_CLOTHING_H
