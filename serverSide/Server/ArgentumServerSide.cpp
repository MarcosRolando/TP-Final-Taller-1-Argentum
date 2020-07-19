#include <iostream>
#include "ArgentumServerSide.h"
#include "ArgentumServer.h"
#include "../Config/Configuration.h"

#define INVALID_ARGUMENTS_MESSAGE "Error: argumentos invalidos."
//#define ARGUMENT_AMOUNT 2
#define ERROR 1
#define SUCCESS 0
//#define PORT_ARG_INDEX 1
//#define MAP_PATH_ARG_INDEX 1

int ArgentumServerSide::run(int argc, char** argv) {
    /*
    if (argc != ARGUMENT_AMOUNT) {
        std::cerr << INVALID_ARGUMENTS_MESSAGE << std::endl;
        return ERROR;
    }
    */
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
