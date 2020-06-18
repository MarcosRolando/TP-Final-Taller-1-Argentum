//
// Created by marcos on 6/6/20.
//

#ifndef ARGENTUM_TPEXCEPTION_H
#define ARGENTUM_TPEXCEPTION_H

#include <exception>
#define BUF_LEN 256

class TPException : public std::exception {
private:
    char errorMessage[BUF_LEN]{};
public:
    explicit TPException(const char *fmt, ...);
    const char * what() const noexcept override;
};


#endif //ARGENTUM_TPEXCEPTION_H
