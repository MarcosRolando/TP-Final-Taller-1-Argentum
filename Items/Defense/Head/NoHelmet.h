//
// Created by marcos on 18/6/20.
//

#ifndef ARGENTUM_NOHELMET_H
#define ARGENTUM_NOHELMET_H

#include "Head.h"

class NoHelmet : public Head {
public:
    NoHelmet();
    bool isDefault() const override;
};


#endif //ARGENTUM_NOHELMET_H
