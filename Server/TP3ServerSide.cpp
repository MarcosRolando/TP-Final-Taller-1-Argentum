#include "TP3ServerSide.h"
#include "ArgentumServer.h"
#include <iostream>

#define INVALID_ARGUMENTS_MESSAGE "Error: argumentos invalidos."
#define ARGUMENT_AMOUNT 3
#define ERROR 1
#define SUCCESS 0

int TP3ServerSide::run(int argc, char** argv) {
    if (argc != ARGUMENT_AMOUNT) {
        std::cerr << INVALID_ARGUMENTS_MESSAGE << std::endl;
        return ERROR;
    }
    try {
        ArgentumServer server(argv[1], argv[2]);
        server.connect();
        //Game::showResults();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    return SUCCESS;
}
