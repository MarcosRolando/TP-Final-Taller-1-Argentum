//
// Created by marcos on 18/6/20.
//

#ifndef ARGENTUM_NOSHIELD_H
#define ARGENTUM_NOSHIELD_H

#include "Shield.h"

class NoShield : public Shield {
public:
    NoShield();
    bool isDefault() const override;
};


#endif //ARGENTUM_NOSHIELD_H
