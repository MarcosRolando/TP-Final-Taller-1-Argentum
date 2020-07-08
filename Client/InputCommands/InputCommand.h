//
// Created by ivan on 7/7/20.
//

#ifndef ARGENTUM_INPUTCOMMAND_H
#define ARGENTUM_INPUTCOMMAND_H
#include <sstream>

class GameGUI;

// Interfaz de los comandos del minichat.

class InputCommand {
public:
    virtual void operator()(GameGUI& game, std::stringstream& msgBuffer) = 0;
};

#endif //ARGENTUM_INPUTCOMMAND_H
