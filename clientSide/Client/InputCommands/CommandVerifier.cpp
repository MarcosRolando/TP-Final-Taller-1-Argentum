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
#include "BuyCommand.h"
#include "ResurrectCommand.h"
#include "HealCommand.h"
#include "DepositCommand.h"
#include "WithdrawCommand.h"
#include "MessageToPlayerCommand.h"
#include "RequestInventoryNamesCommand.h"
#include "../GameGUI.h"

CommandVerifier::CommandVerifier() {
    _initCommands();
}

/* Inicializa el unordered_map de comandos */
void CommandVerifier::_initCommands() {
    commands.emplace("/meditate", GameType::PLAYER_MEDITATE);
    commands.emplace("/revive", GameType::PLAYER_RESURRECT);
    commands.emplace("/heal", GameType::PLAYER_HEAL);
    commands.emplace("/deposit", GameType::PLAYER_DEPOSIT);
    commands.emplace("/withdraw", GameType::PLAYER_WITHDRAW);
    commands.emplace("/list", GameType::PLAYER_LIST);
    commands.emplace("/buy", GameType::PLAYER_BUY);
    commands.emplace("/sell", GameType::PLAYER_SELL);
    commands.emplace("/take", GameType::PLAYER_PICK_UP);
    commands.emplace("/drop", GameType::PLAYER_DROP);
    commands.emplace("/inventory", GameType::PLAYER_REQUEST_INVENTORY_NAMES);
}

std::unique_ptr<InputCommand> CommandVerifier::verifyCommand(GameGUI& game,
        std::string&& inputCmd) {
    std::unique_ptr<InputCommand> command;
    input = inputCmd;

    //Agarro lo que tenga antes de un espacio. Eso deberia ser el comando
    std::string cmd = input.substr(0, input.find(' ', 0));
    GameType::PlayerEvent event;
    if (cmd.front() == '@') {//Antes de ver si es un comando veo si es un nickname
        command = _processSendMessageToPlayer();
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
                    command = _processResurrect(game);
                    break;
                case GameType::PLAYER_HEAL:
                    command = _processHeal(game);
                    break;
                case GameType::PLAYER_BUY:
                    command = _processBuy(game);
                    break;
                case GameType::PLAYER_SELL:
                    command = _processSell(game);
                    break;
                case GameType::PLAYER_WITHDRAW:
                    command = _processWithdraw(game);
                    break;
                case GameType::PLAYER_DEPOSIT:
                    command = _processDeposit(game);
                    break;
                case GameType::PLAYER_MEDITATE:
                    command = _processMeditate();
                    break;
                case GameType::PLAYER_REQUEST_INVENTORY_NAMES:
                    command = _processRequestInventoryNames();
                    break;
                default:
                    break;
            }
        } catch (std::exception& e) {
            //Si no encuentra el comando en el unordered_map es que no es un comando
            //valido asi que devuelvo nullptr
            return nullptr;
        }
    }
    return command;
}

std::unique_ptr<InputCommand> CommandVerifier::_processRequestInventoryNames() {
    //Chequeo que no haya nada escrito despues del comando
    if (input.size() > input.find(' ', 0)) {
        return nullptr;
    }
    return std::unique_ptr<InputCommand>(new RequestInventoryNamesCommand());
}

std::unique_ptr<InputCommand> CommandVerifier::_processMeditate() {
    //Chequeo que no haya nada escrito despues del comando
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
    return std::unique_ptr<InputCommand>(new ResurrectCommand(game.getSelector().getSelectedTile()));
}

std::unique_ptr<InputCommand> CommandVerifier::_processHeal(GameGUI& game) {
    //Chequeo que no haya nada escrito despues del comando
    if (input.size() > input.find(' ', 0)) {
        return nullptr;
    }
    return std::unique_ptr<InputCommand>(new HealCommand(game.getSelector().getSelectedTile()));
}

std::unique_ptr<InputCommand> CommandVerifier::_processSell(GameGUI& game) {
    std::string parameters;
    if (input.size() > input.find(' ', 0)) {
        //Agarro lo que haya dsps del espacio que deberia ser el item que quiero vender
        parameters = input.substr(input.find(' ', 0) + 1, input.size());
        if (!parameters.empty()) {
            return std::unique_ptr<InputCommand>(new SellCommand(
                    game.getSelector().getSelectedTile(), std::move(parameters)));
        }
    }
    return nullptr;
}

std::unique_ptr<InputCommand> CommandVerifier::_processBuy(GameGUI& game) {
    std::string parameters;
    if (input.size() > input.find(' ', 0)) {
        //Agarro lo que haya dsps del espacio que deberian ser los parametros
        parameters = input.substr(input.find(' ', 0) + 1, input.size());
        if (!parameters.empty()) {
            return std::unique_ptr<InputCommand>(new BuyCommand(
                    game.getSelector().getSelectedTile(), std::move(parameters)));
        }
    }
    return nullptr;
}

std::unique_ptr<InputCommand> CommandVerifier::_processDeposit(GameGUI& game) {
    std::string parameters;
    int separator = input.find(' ', 0);
    if ((int)input.size() > separator && separator != -1) {
        //Agarro lo que haya dsps del espacio que deberian ser los parametros
        parameters = input.substr(separator + 1, input.size());
        //Como para el gold tambien necesito una cantidad lo proceso distinto a un item
        if (parameters.find("Gold", 0) != std::string::npos) {
            _processGold(parameters);
        }
        if (!parameters.empty()){
            return std::unique_ptr<InputCommand>(new DepositCommand(
                    game.getSelector().getSelectedTile(), std::move(parameters)));
        }
    }
    return nullptr;
}

std::unique_ptr<InputCommand> CommandVerifier::_processWithdraw(GameGUI& game) {
    std::string parameters;
    int separator = input.find(' ', 0);
    if ((int)input.size() > separator && separator != -1) {
        //Agarro lo que haya dsps del espacio que deberian ser los parametros
        parameters = input.substr(separator + 1, input.size());
        //Como para el gold tambien necesito una cantidad lo proceso distinto a un item
        if (parameters.find("Gold", 0) != std::string::npos) {
            _processGold(parameters);
        }
        if (!parameters.empty()){
            return std::unique_ptr<InputCommand>(new WithdrawCommand(
                    game.getSelector().getSelectedTile(), std::move(parameters)));
        }
    }
    return nullptr;
}

void CommandVerifier::_processGold(std::string& parameter) {
    int separator = parameter.find(' ', 0);
    if ((int)parameter.size() > separator && separator != -1) {
        //Agarro la parte del string que deberia tener la cantidad de gold
        std::string goldAmount = parameter.substr(parameter.find(' ', 0) + 1,
                                                  parameter.size());
        try {
            std::stoi(goldAmount);
        } catch (std::exception &e) {
            parameter = "";//Si la cantidad no es un numero
        }
    } else {
        parameter = "";//Si no tengo una cantidad de oro
    }
}

std::unique_ptr<InputCommand> CommandVerifier::_processSendMessageToPlayer() {
    int separator = input.find(' ');
    if ((int)input.size() > separator && separator != -1) {
        std::string nickname = input.substr(1, separator-1);
        std::string msg = input.substr(separator + 1, input.size());
        if (!msg.empty()) {
            return std::unique_ptr<InputCommand>(new MessageToPlayerCommand(
                    std::move(nickname), std::move(msg)));
        }
    }
    return nullptr;
}
