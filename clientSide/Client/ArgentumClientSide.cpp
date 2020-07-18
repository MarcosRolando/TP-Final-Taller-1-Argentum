#include "ArgentumClientSide.h"
#include "ArgentumClient.h"
#include <iostream>

#define INVALID_ARGUMENTS_MESSAGE "Error: Invalid Arguments."
#define ARGUMENT_AMOUNT 1

int ArgentumClientSide::run(int argc) {
    if (argc != ARGUMENT_AMOUNT) {
        std::cout << INVALID_ARGUMENTS_MESSAGE << std::endl;
        return EXIT_FAILURE;
    }
    try {
        Client client;
        client.run();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
