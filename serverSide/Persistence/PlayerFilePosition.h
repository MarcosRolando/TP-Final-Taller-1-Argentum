//
// Created by marcos on 7/8/20.
//

#ifndef ARGENTUM_PLAYERFILEPOSITION_H
#define ARGENTUM_PLAYERFILEPOSITION_H

/*Este struct se usa para saber el offset de un player en el archivo (donde comienza)
 * y la longitud que ocupan sus datos en este*/

struct PlayerFilePosition {
    uint32_t offset;
    uint32_t length;
};

#endif //ARGENTUM_PLAYERFILEPOSITION_H
