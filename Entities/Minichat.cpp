//
// Created by marcos on 7/3/20.
//

#include "Minichat.h"

void Minichat::addMessage(std::string&& msg) {
    message += msg;
}

std::string Minichat::getMessages() const {
    return message;
}

void Minichat::clear() {
    message.clear();
}
