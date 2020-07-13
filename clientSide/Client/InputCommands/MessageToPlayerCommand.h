//
// Created by ivan on 10/7/20.
//

#ifndef ARGENTUM_MESSAGETOPLAYERCOMMAND_H
#define ARGENTUM_MESSAGETOPLAYERCOMMAND_H
#include "InputCommand.h"
#include "../../Map/Coordinate.h"

class MessageToPlayerCommand : public InputCommand{
private:
    std::string nickname, msg;
public:
    MessageToPlayerCommand(std::string&& nickname, std::string&& msg) : nickname(nickname),
    msg(msg) {}
    void operator()(std::stringstream& msgBuffer) override;

};


#endif //ARGENTUM_MESSAGETOPLAYERCOMMAND_H
