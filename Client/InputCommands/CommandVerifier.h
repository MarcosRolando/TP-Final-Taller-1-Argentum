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
    std::string input;

public:
    CommandVerifier();
    std::unique_ptr<InputCommand> verifyCommand(GameGUI& game, std::string&& cmd);

private:
    std::unique_ptr<InputCommand> _processMeditate();
    std::unique_ptr<InputCommand> _processPickUp();
    void _initCommands();
    void _initItems();

    std::unique_ptr<InputCommand> _processDrop(GameGUI& game);

    std::unique_ptr<InputCommand> _processList(GameGUI &game);

    std::unique_ptr<InputCommand> _processResurrect(GameGUI &game);

    std::unique_ptr<InputCommand> _processSell(GameGUI &game);
};


#endif //ARGENTUM_COMMANDVERIFIER_H
