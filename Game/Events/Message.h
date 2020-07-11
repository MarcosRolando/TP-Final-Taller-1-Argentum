//
// Created by marcos on 7/10/20.
//

#ifndef ARGENTUM_MESSAGE_H
#define ARGENTUM_MESSAGE_H

#include "Event.h"
#include <string>

class Game;
class Entity;

class Message : public Event {
private:
    Game& game;
    std::string playerToMessage;
    std::string message;

public:
    Message(Game& _game, Entity& _playerWhoMessaged, std::string&& _playerToMessage,
            std::string&& _message);

    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_MESSAGE_H
