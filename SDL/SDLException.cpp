//
// Created by marcos on 6/6/20.
//

#include "SDLException.h"
#include <SDL.h>

SDLException::SDLException(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(errorMessage, BUF_LEN, fmt, args);
    va_end(args);
    errorMessage[BUF_LEN - 1] = 0;
}

const char *SDLException::what() const noexcept {
    return errorMessage;
}


