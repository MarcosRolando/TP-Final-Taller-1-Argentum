#include "ArgentumClientSide.h"
#include "ArgentumClient.h"
#include <iostream>

#define INVALID_ARGUMENTS_MESSAGE "Error: argumentos invalidos."
#define ARGUMENT_AMOUNT 3

int ArgentumClientSide::run(int argc, char** argv) {
    if (argc != ARGUMENT_AMOUNT) {
        std::cout << INVALID_ARGUMENTS_MESSAGE << std::endl;
        return EXIT_FAILURE;
    }
    try {
        Client client(argv[1], argv[2]);
        client.connect();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}