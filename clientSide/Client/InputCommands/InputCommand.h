//
// Created by ivan on 7/7/20.
//

#ifndef ARGENTUM_INPUTCOMMAND_H
#define ARGENTUM_INPUTCOMMAND_H

#include <sstream>
#include <msgpack.hpp>
#include "../../../libs/GameEnums.h"

// Interfaz de los comandos del minichat.

class InputCommand {
public:
    virtual void operator()(std::stringstream& msgBuffer) = 0;
    virtual ~InputCommand() = default;
};

#endif //ARGENTUM_INPUTCOMMAND_H
