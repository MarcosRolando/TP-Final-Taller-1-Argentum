//
// Created by ivan on 7/7/20.
//

#include <sstream>
#include "CommandVerifier.h"

std::unique_ptr<InputCommand>
CommandVerifier::verifyCommand(std::string&& inputCmd) {
    std::istringstream stream(inputCmd);
    std::string cmd;//Me fijo que comando es y de ahi veo si necesita parametros
    //test >> sTest;
    //test >> sTest;
    return std::unique_ptr<InputCommand>();
}
