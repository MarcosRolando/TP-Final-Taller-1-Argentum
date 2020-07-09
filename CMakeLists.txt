cmake_minimum_required(VERSION 3.16)
project(Argentum)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(jsoncpp)
include_directories(${jsoncpp_INCLUDE_DIRS})

add_subdirectory(Texture)
add_subdirectory(Map)
add_subdirectory(Character)

add_executable(argentumClient main.cpp TPException.cpp TPException.h
SDL/Sound/SoundRepository.cpp SDL/Sound/SoundRepository.h SDL/Text/Font.cpp
SDL/Text/Font.h Configuration/ConfigFileReader.cpp Configuration/ConfigFileReader.h
Configuration/Configuration.cpp Configuration/Configuration.h SDL/Sound/Sound.cpp
SDL/Sound/Sound.h Configuration/Calculator.cpp Configuration/Calculator.h
Map/Tile.cpp Map/Tile.h Map/Map.cpp Map/Map.h Character/Player.cpp
Character/Player.h Timer.cpp Timer.h GameConstants.h Character/NPC.cpp
Character/NPC.h Character/Entity.cpp Character/Entity.h
Screen/Window.cpp Screen/Window.h SDL/Text/Text.cpp SDL/Text/Text.h SDL/GUI/PlayerInfoGUI.cpp
SDL/GUI/PlayerInfoGUI.h SDL/GUI/PlayerInventoryGUI.cpp SDL/GUI/PlayerInventoryGUI.h
Spells/Spell.cpp Spells/Spell.h MapFileReader.cpp MapFileReader.h SDL/Minichat/Minichat.cpp
SDL/Minichat/Minichat.h SDL/Selector.cpp SDL/Selector.h SDL/Sound/SoundPlayer.cpp
SDL/Sound/SoundPlayer.h Screen/MainMenu.cpp Screen/MainMenu.h
Client/ClientProtocol.cpp Client/ClientProtocol.h Client/ArgentumClientSide.cpp
Client/ArgentumClientSide.h Client/ArgentumClient.cpp Client/ArgentumClient.h
Client/Socket.cpp Client/Socket.h Client/Thread.cpp Client/Thread.h
Client/User.cpp Client/User.h Client/GameGUI.cpp Client/GameGUI.h
        Shared/GameEnums.h Client/ProtocolEnumTranslator.cpp
        Client/ProtocolEnumTranslator.h Client/ClientEventHandler.cpp Client/ClientEventHandler.h
        Client/BlockingQueue.hpp Client/UpdateReceiver.cpp Client/UpdateReceiver.h
        UpdateEvents/UpdateEvent.h UpdateEvents/UpdateMove.cpp UpdateEvents/UpdateMove.h
        Client/UpdateQueue.hpp UpdateEvents/UpdateCreatePlayer.cpp UpdateEvents/UpdateCreatePlayer.h
        Client/GameInitializer.cpp Client/GameInitializer.h SDL/GUI/GUIPlayerInfo.h UpdateEvents/UpdateCreateNPC.cpp
        UpdateEvents/UpdateCreateNPC.h Client/EntityData.h UpdateEvents/UpdateGUI.cpp UpdateEvents/UpdateGUI.h
        UpdateEvents/UpdateRemoveEntity.cpp UpdateEvents/UpdateRemoveEntity.h UpdateEvents/UpdateEquip.cpp
        UpdateEvents/UpdateEquip.h UpdateEvents/UpdateCreateItem.cpp UpdateEvents/UpdateCreateItem.h
        UpdateEvents/UpdatePlayerDeath.cpp UpdateEvents/UpdatePlayerDeath.h UpdateEvents/UpdateAttack.cpp
        UpdateEvents/UpdateAttack.h Client/InputCommands/InputCommand.h Client/InputCommands/CommandVerifier.cpp
        Client/InputCommands/CommandVerifier.h Client/InputCommands/MeditateCommand.cpp Client/InputCommands/MeditateCommand.h
        Client/InputCommands/PickUpCommand.cpp Client/InputCommands/PickUpCommand.h Client/CitizenData.h
UpdateEvents/UpdateDestroyItem.cpp UpdateEvents/UpdateDestroyItem.h)


target_compile_options (argentumClient PUBLIC -std=c++11 -Wall -Werror -pedantic
        -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -ljsoncpp)

target_link_options(argentumClient PUBLIC -lm -pthread)


target_link_libraries(argentumClient jsoncpp ${Boost_LIBRARIES} )

target_link_libraries(argentumClient ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer
                        texture map character)
