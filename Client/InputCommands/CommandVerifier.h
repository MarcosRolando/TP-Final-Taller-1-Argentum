//
// Created by ivan on 7/7/20.
//

#ifndef ARGENTUM_COMMANDVERIFIER_H
#define ARGENTUM_COMMANDVERIFIER_H

#include "InputCommand.h"

#include <memory>

class CommandVerifier {
private:

public:
    static std::unique_ptr<InputCommand> verifyCommand(std::string&& cmd);
};


#endif //ARGENTUM_COMMANDVERIFIER_H
