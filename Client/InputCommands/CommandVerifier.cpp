//
// Created by ivan on 7/7/20.
//

#include <sstream>
#include "CommandVerifier.h"
#include "MeditateCommand.h"
#include "PickUpCommand.h"
#include "DropCommand.h"
#include "ListCommand.h"
#include "SellCommand.h"
#include "../GameGUI.h"

CommandVerifier::CommandVerifier() {
    _initCommands();
    _initItems();
}

void CommandVerifier::_initCommands() {
    commands.emplace("/meditate", GameType::PLAYER_MEDITATE);
    commands.emplace("/resurrect", GameType::PLAYER_RESURRECT);
    //commands.emplace("/heal", GameType::PLAYER_HEAL);
    commands.emplace("/deposit", GameType::PLAYER_DEPOSIT);
    commands.emplace("/withdraw", GameType::PLAYER_WITHDRAW);
    commands.emplace("/list", GameType::PLAYER_LIST);
    commands.emplace("/buy", GameType::PLAYER_BUY);
    commands.emplace("/sell", GameType::PLAYER_SELL);
    commands.emplace("/take", GameType::PLAYER_PICK_UP);
    commands.emplace("/drop", GameType::PLAYER_DROP);
}

void CommandVerifier::_initItems() {
    items.emplace("longsword", GameType::LONGSWORD);
    items.emplace("axe", GameType::AXE);
    items.emplace("warhammer", GameType::WARHAMMER);
    items.emplace("ash rod", GameType::ASH_ROD);
    items.emplace("elven flute", GameType::ELVEN_FLUTE);
    items.emplace("linked staff", GameType::LINKED_STAFF);
    items.emplace("simple bow", GameType::SIMPLE_BOW);
    items.emplace("composite bow", GameType::COMPOSITE_BOW);
    items.emplace("gnarled staff", GameType::GNARLED_STAFF);

    items.emplace("leather armor", GameType::LEATHER_ARMOR);
    items.emplace("plate armor", GameType::PLATE_ARMOR);
    items.emplace("blue tunic", GameType::BLUE_TUNIC);
    items.emplace("hood", GameType::HOOD);
    items.emplace("iron helmet", GameType::IRON_HELMET);
    items.emplace("turtle shield", GameType::TURTLE_SHIELD);
    items.emplace("iron shield", GameType::IRON_SHIELD);
    items.emplace("magic hat", GameType::MAGIC_HAT);
    items.emplace("health potion", GameType::HEALTH_POTION);
    items.emplace("mana potion", GameType::MANA_POTION);
}

std::unique_ptr<InputCommand> CommandVerifier::verifyCommand(GameGUI& game,
        std::string&& inputCmd) {
    std::unique_ptr<InputCommand> command;
    input = inputCmd;

    //Agarro lo que tenga antes de un espacio. Eso deberia ser el comando
    std::string cmd = input.substr(0, input.find(' ', 0));
    GameType::PlayerEvent event;
    if (cmd.back() == '@') {
        //_processSendMessageToPlayer();
    } else {
        try {
            event = commands.at(cmd);
            switch (event) {
                case GameType::PLAYER_PICK_UP:
                    command = _processPickUp();
                    break;
                case GameType::PLAYER_DROP:
                    command = _processDrop(game);
                    break;
                case GameType::PLAYER_LIST:
                    command = _processList(game);
                    break;
                case GameType::PLAYER_RESURRECT:
                    //command = _processResurrect(game);
                    break;
                case GameType::PLAYER_BUY:
                    //command = _processBuy(std::move(inputCmd));
                    break;
                case GameType::PLAYER_SELL:
                    command = _processSell(game);
                    break;
                case GameType::PLAYER_WITHDRAW:
                    //command = _processWithdraw(std::move(inputCmd));
                    break;
                case GameType::PLAYER_DEPOSIT:
                    //command = _processDeposit(std::move(inputCmd));
                    break;
                case GameType::PLAYER_MEDITATE:
                    _processMeditate();
                    break;
                default:
                    break;
            }
        } catch (std::exception& e) {
            return nullptr;
        }
    }


    /*//Agarro lo que haya dsps del espacio que deberian ser los parametros
    std::string parameters;
    if (inputCmd.size() > inputCmd.find(' ', 0)) {
        parameters = inputCmd.substr(inputCmd.find(' ', 0), inputCmd.size());
    }*/
    return command;
}

std::unique_ptr<InputCommand> CommandVerifier::_processMeditate() {
    if (input.size() > input.find(' ', 0)) {
        return nullptr;
    }
    return std::unique_ptr<InputCommand>(new MeditateCommand());
}

std::unique_ptr<InputCommand> CommandVerifier::_processPickUp() {
    //Chequeo que no haya nada escrito despues del comando
    if (input.size() > input.find(' ', 0)) {
        return nullptr;
    }
    return std::unique_ptr<InputCommand>(new PickUpCommand());
}

std::unique_ptr<InputCommand> CommandVerifier::_processDrop(GameGUI& game) {
    //Chequeo que no haya nada escrito despues del comando
    if (input.size() > input.find(' ', 0)) {
        return nullptr;
    }
    return std::unique_ptr<InputCommand>(new DropCommand(game.getSelector().getInventorySlot()));
}

std::unique_ptr<InputCommand> CommandVerifier::_processList(GameGUI& game) {
    //Chequeo que no haya nada escrito despues del comando
    if (input.size() > input.find(' ', 0)) {
        return nullptr;
    }
    return std::unique_ptr<InputCommand>(new ListCommand(game.getSelector().getSelectedTile()));
}

std::unique_ptr<InputCommand> CommandVerifier::_processResurrect(GameGUI& game) {
    //Chequeo que no haya nada escrito despues del comando
    if (input.size() > input.find(' ', 0)) {
        return nullptr;
    }
    return std::unique_ptr<InputCommand>(new ListCommand(game.getSelector().getSelectedTile()));
}

std::unique_ptr<InputCommand> CommandVerifier::_processSell(GameGUI& game) {
    //Agarro lo que haya dsps del espacio que deberian ser los parametros
    std::string parameters;
    if (input.size() > input.find(' ', 0)) {
        parameters = input.substr(input.find(' ', 0), input.size());
    }
    return std::unique_ptr<InputCommand>(new SellCommand(
            game.getSelector().getSelectedTile(), std::move(parameters)));
}
