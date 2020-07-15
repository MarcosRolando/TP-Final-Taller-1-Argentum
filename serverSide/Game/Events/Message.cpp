//
// Created by marcos on 7/10/20.
//

#include "Message.h"
#include "../../Entities/Player.h"
#include "../Game.h"

void Message::operator()(ServerProtocol &protocol) {
    game.messagePlayer(playerWhoMessaged, playerToMessage, message);
}

Message::Message(Game &_game, Player &_playerWhoMessaged,
                 std::string &&_playerToMessage, std::string &&_message)
                 : game(_game), playerWhoMessaged(_playerWhoMessaged), playerToMessage(std::move(_playerToMessage)) {

    message = _playerWhoMessaged.getNickname() + ": " + _message;
}
