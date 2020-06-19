//
// Created by marcos on 18/6/20.
//

#ifndef ARGENTUM_FIST_H
#define ARGENTUM_FIST_H

#include "Weapon.h"

class Fist : public Weapon {
public:
    Fist();
    bool isDefault() override;
};


#endif //ARGENTUM_FIST_H
