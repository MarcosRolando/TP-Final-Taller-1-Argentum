//
// Created by ivan on 7/7/20.
//

#ifndef ARGENTUM_COMMANDVERIFIER_H
#define ARGENTUM_COMMANDVERIFIER_H

#include "../../../libs/GameEnums.h"
#include "InputCommand.h"
#include <memory>
#include <unordered_map>

class GameGUI;

class CommandVerifier {
private:
    std::unordered_map<std::string, GameType::PlayerEvent> commands;
    std::string input;

public:
    /* Constructor */
    CommandVerifier();
    /* Verifica que comando ingrese y devuelve el functor */
    std::unique_ptr<InputCommand> verifyCommand(GameGUI& game, std::string&& cmd);

private:
    void _initCommands();
    std::unique_ptr<InputCommand> _processMeditate();
    std::unique_ptr<InputCommand> _processPickUp();
    std::unique_ptr<InputCommand> _processDrop(GameGUI& game);
    std::unique_ptr<InputCommand> _processList(GameGUI &game);
    std::unique_ptr<InputCommand> _processResurrect(GameGUI &game);
    std::unique_ptr<InputCommand> _processSell(GameGUI &game);
    std::unique_ptr<InputCommand> _processBuy(GameGUI &game);
    std::unique_ptr<InputCommand> _processHeal(GameGUI& game);
    std::unique_ptr<InputCommand> _processDeposit(GameGUI &game);
    std::unique_ptr<InputCommand> _processWithdraw(GameGUI &game);
    std::unique_ptr<InputCommand> _processSendMessageToPlayer();
    std::unique_ptr<InputCommand> _processRequestInventoryNames();

    static void _processGold(std::string &parameter);

};


#endif //ARGENTUM_COMMANDVERIFIER_H
