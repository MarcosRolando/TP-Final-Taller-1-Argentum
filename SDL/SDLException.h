//
// Created by marcos on 6/6/20.
//

#ifndef ARGENTUM_SDLEXCEPTION_H
#define ARGENTUM_SDLEXCEPTION_H

#include <exception>
#define BUF_LEN 256

class SDLException : public std::exception {
private:
    char errorMessage[BUF_LEN]{};
public:
    explicit SDLException(const char *fmt, ...);
    const char * what() const noexcept override;
};


#endif //ARGENTUM_SDLEXCEPTION_H
