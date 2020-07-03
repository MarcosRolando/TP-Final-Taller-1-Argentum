//
// Created by marcos on 7/3/20.
//

#ifndef ARGENTUM_MINICHAT_H
#define ARGENTUM_MINICHAT_H

#include <string>

class Minichat {
private:
    std::string message;

public:
    void addMessage(std::string&& msg);
    std::string getMessages() const;
    void clear();
};


#endif //ARGENTUM_MINICHAT_H
