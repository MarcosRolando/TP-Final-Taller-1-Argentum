cmake_minimum_required(VERSION 3.16)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(jsoncpp)
include_directories(${jsoncpp_INCLUDE_DIRS})

add_subdirectory(Texture)
add_subdirectory(Map)
add_subdirectory(Character)

add_executable(argentumClient clientMain.cpp ../libs/TPException.cpp ../libs/TPException.h
        Sound/SoundRepository.cpp Sound/SoundRepository.h Graphics/Text/Font.cpp
        Graphics/Text/Font.h Sound/Sound.cpp
        Sound/Sound.h
        Map/Tile.cpp Map/Tile.h Map/Map.cpp Map/Map.h Character/Player.cpp
        Character/Player.h Client/GameConstants.h Character/NPC.cpp
        Character/NPC.h Character/Entity.cpp Character/Entity.h
        Screen/Window.cpp Screen/Window.h Graphics/Text/Text.cpp Graphics/Text/Text.h Graphics/GUI/PlayerInfoGUI.cpp
        Graphics/GUI/PlayerInfoGUI.h Graphics/GUI/PlayerInventoryGUI.cpp Graphics/GUI/PlayerInventoryGUI.h
        Spells/Spell.cpp Spells/Spell.h Graphics/Minichat/Minichat.cpp
        Graphics/Minichat/Minichat.h Graphics/Selector.cpp Graphics/Selector.h Sound/SoundPlayer.cpp
        Sound/SoundPlayer.h Screen/MainMenu.cpp Screen/MainMenu.h
        Client/ClientProtocol.cpp Client/ClientProtocol.h Client/ArgentumClientSide.cpp
        Client/ArgentumClientSide.h Client/ArgentumClient.cpp Client/ArgentumClient.h
        ../libs/Socket.cpp ../libs/Socket.h ../libs/Thread.cpp ../libs/Thread.h
        Client/User.cpp Client/User.h Client/GameGUI.cpp Client/GameGUI.h
        ../libs/GameEnums.h Client/ProtocolEnumTranslator.cpp
        Client/ProtocolEnumTranslator.h Client/ClientEventHandler.cpp Client/ClientEventHandler.h
        Client/BlockingQueue.hpp Client/UpdateReceiver.cpp Client/UpdateReceiver.h
        UpdateEvents/UpdateEvent.h UpdateEvents/UpdateMove.cpp UpdateEvents/UpdateMove.h
        Client/UpdateQueue.hpp UpdateEvents/UpdateCreatePlayer.cpp UpdateEvents/UpdateCreatePlayer.h
        Client/GameInitializer.cpp Client/GameInitializer.h Graphics/GUI/GUIPlayerInfo.h UpdateEvents/UpdateCreateNPC.cpp
        UpdateEvents/UpdateCreateNPC.h Client/EntityData.h UpdateEvents/UpdateGUI.cpp UpdateEvents/UpdateGUI.h
        UpdateEvents/UpdateRemoveEntity.cpp UpdateEvents/UpdateRemoveEntity.h UpdateEvents/UpdateEquip.cpp
        UpdateEvents/UpdateEquip.h UpdateEvents/UpdateCreateItem.cpp UpdateEvents/UpdateCreateItem.h
        UpdateEvents/UpdatePlayerDeath.cpp UpdateEvents/UpdatePlayerDeath.h UpdateEvents/UpdateAttack.cpp
        UpdateEvents/UpdateAttack.h Client/InputCommands/InputCommand.h Client/InputCommands/CommandVerifier.cpp
        Client/InputCommands/CommandVerifier.h Client/InputCommands/MeditateCommand.cpp Client/InputCommands/MeditateCommand.h
        Client/InputCommands/PickUpCommand.cpp Client/InputCommands/PickUpCommand.h Client/CitizenData.h
        UpdateEvents/UpdateDestroyItem.cpp UpdateEvents/UpdateDestroyItem.h Client/InputCommands/DropCommand.cpp
        Client/InputCommands/DropCommand.h Client/InputCommands/ListCommand.cpp Client/InputCommands/ListCommand.h
        Client/InputCommands/ResurrectCommand.cpp Client/InputCommands/ResurrectCommand.h
        Client/InputCommands/SellCommand.cpp Client/InputCommands/SellCommand.h Client/InputCommands/BuyCommand.cpp
        Client/InputCommands/BuyCommand.h UpdateEvents/UpdatePlayerResurrect.cpp UpdateEvents/UpdatePlayerResurrect.h
        Client/InputCommands/HealCommand.cpp Client/InputCommands/HealCommand.h UpdateEvents/UpdateTeleportEntity.h
        UpdateEvents/UpdateTeleportEntity.cpp Client/InputCommands/DepositCommand.cpp Client/InputCommands/DepositCommand.h Client/InputCommands/WithdrawCommand.cpp Client/InputCommands/WithdrawCommand.h Client/InputCommands/MessageToPlayerCommand.cpp Client/InputCommands/MessageToPlayerCommand.h)



target_compile_options (argentumClient PUBLIC -std=c++11 -Wall -Werror -pedantic
        -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -ljsoncpp)

target_link_options(argentumClient PUBLIC -lm -pthread)

target_link_libraries(argentumClient jsoncpp ${Boost_LIBRARIES} )

target_link_libraries(argentumClient ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer
                        texture map character)
