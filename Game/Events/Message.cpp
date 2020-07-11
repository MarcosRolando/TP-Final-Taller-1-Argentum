//
// Created by marcos on 7/10/20.
//

#include "Message.h"
#include "../../Entities/Entity.h"
#include "../Game.h"

void Message::operator()(ServerProtocol &protocol) {
    game.messagePlayer(playerToMessage, message);
}

Message::Message(Game &_game, Entity &_playerWhoMessaged,
                 std::string &&_playerToMessage, std::string &&_message)
                 : game(_game), playerToMessage(std::move(_playerToMessage)) {

    message = _playerWhoMessaged.getNickname() + ": " + _message;
}
