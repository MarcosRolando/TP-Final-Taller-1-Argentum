//
// Created by marcos on 9/7/20.
//

#ifndef ARGENTUM_CITIZENDATA_H
#define ARGENTUM_CITIZENDATA_H

#include "../Texture/TextureID.h"
#include <string>


 /*Se usa cuando cargo la data inicial de los tiles, por si tienen un citizen
  * (trader, banker, etc)*/
struct CitizenData {
    TextureID texture;
    std::string nickname;
};

#endif //ARGENTUM_CITIZENDATA_H
