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
    /*Agrega un mensaje al minichat del player*/
    void addMessage(std::string&& msg);
    void addMessage(const std::string& msg);

    /*Retorna el string del minichat (el minichat en si digamos)*/
    std::string getMessages() const;

    /*Limpia el minichat (elimina el string)*/
    void clear();
};


#endif //ARGENTUM_MINICHAT_H
