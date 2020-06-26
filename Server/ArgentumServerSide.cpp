#include "ArgentumServerSide.h"
#include "ArgentumServer.h"
#include <iostream>

#define INVALID_ARGUMENTS_MESSAGE "Error: argumentos invalidos."
#define ARGUMENT_AMOUNT 3
#define ERROR 1
#define SUCCESS 0
#define PORT_ARG_INDEX 1
#define MAP_PATH_ARG_INDEX 2

int ArgentumServerSide::run(int argc, char** argv) {
    if (argc != ARGUMENT_AMOUNT) {
        std::cerr << INVALID_ARGUMENTS_MESSAGE << std::endl;
        return ERROR;
    }
    try {
        ArgentumServer server/*(argv[PORT_ARG_INDEX], argv[MAP_PATH_ARG_INDEX])*/;
        server.connect(argv[PORT_ARG_INDEX], argv[MAP_PATH_ARG_INDEX]);
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    return SUCCESS;
}
