//
// Created by ivan on 7/7/20.
//

#ifndef ARGENTUM_COMMANDVERIFIER_H
#define ARGENTUM_COMMANDVERIFIER_H

#include "InputCommand.h"

#include <memory>

class CommandVerifier {
public:
    static std::unique_ptr<InputCommand> verifyCommand(std::string&& cmd);

private:
    static std::unique_ptr<InputCommand> _processMeditateCommand();
};


#endif //ARGENTUM_COMMANDVERIFIER_H
