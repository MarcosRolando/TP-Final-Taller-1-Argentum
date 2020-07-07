//
// Created by ivan on 7/7/20.
//

#include <sstream>
#include "CommandVerifier.h"

std::unique_ptr<InputCommand> CommandVerifier::verifyCommand(std::string&& inputCmd) {
    std::unique_ptr<InputCommand> command;
    std::istringstream stream(inputCmd);
    std::string cmd;//Me fijo que comando es y de ahi veo si necesita parametros
    stream >> cmd;
    if (cmd == "/meditate") {
        //_processMeditateCommand();
    } else if (cmd == "/resurrect") {

    } else if (cmd == "/heal") {

    } else if (cmd == "/deposit") {

    } else if (cmd == "/withdraw") {

    } else if (cmd == "/list") {

    } else if (cmd == "/buy") {

    } else if (cmd == "/sell") {

    } else if (cmd == "/take") {

    } else if (cmd == "/drop") {

    } else if (cmd.back() == '@') {//Veo si es un nickname

    } else {
        //Invalid Command
    }
    return command;
}
