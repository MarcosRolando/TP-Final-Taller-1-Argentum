#include <iostream>
#include "ArgentumServerSide.h"
#include "ArgentumServer.h"
#include "../Config/Configuration.h"

#define INVALID_ARGUMENTS_MESSAGE "Error: argumentos invalidos."
#define ERROR 1
#define SUCCESS 0

int ArgentumServerSide::run(int argc, char** argv) {
    try {
        ArgentumServer server;
        Configuration& config = Configuration::getInstance();
        server.connect(config.configPort(), config.configMapPath());
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    return SUCCESS;
}
