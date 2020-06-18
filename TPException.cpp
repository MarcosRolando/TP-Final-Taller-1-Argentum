//
// Created by marcos on 6/6/20.
//

#include "TPException.h"
#include <SDL.h>

TPException::TPException(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(errorMessage, BUF_LEN, fmt, args);
    va_end(args);
    errorMessage[BUF_LEN - 1] = 0;
}

const char *TPException::what() const noexcept {
    return errorMessage;
}


