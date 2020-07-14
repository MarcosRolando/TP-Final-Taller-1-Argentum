cmake_minimum_required(VERSION 3.16)

add_library(inputCommands BuyCommand.cpp CommandVerifier.cpp DepositCommand.cpp
            DropCommand.cpp HealCommand.cpp ListCommand.cpp MeditateCommand.cpp
            MessageToPlayerCommand.cpp PickUpCommand.cpp ResurrectCommand.cpp
            SellCommand.cpp WithdrawCommand.cpp RequestInventoryNamesCommand.cpp
        RequestInventoryNamesCommand.h)

