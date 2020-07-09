//
// Created by ivan on 7/7/20.
//

#ifndef ARGENTUM_COMMANDVERIFIER_H
#define ARGENTUM_COMMANDVERIFIER_H

#include "../../Shared/GameEnums.h"
#include "InputCommand.h"
#include <memory>
#include <unordered_map>

class GameGUI;

class CommandVerifier {
private:
    std::unordered_map<std::string, GameType::PlayerEvent> commands;
    std::unordered_map<std::string, int32_t> items;

public:
    CommandVerifier();
    std::unique_ptr<InputCommand> verifyCommand(GameGUI& game, std::string&& cmd);

private:
    static std::unique_ptr<InputCommand> _processMeditate();
    static std::unique_ptr<InputCommand> _processPickUp(std::string &&cmd);
    void _initCommands();
    void _initItems();
};


#endif //ARGENTUM_COMMANDVERIFIER_H
