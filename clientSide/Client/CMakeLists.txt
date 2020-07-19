cmake_minimum_required(VERSION 3.16)

add_library(client ArgentumClient.cpp ArgentumClientSide.cpp BlockingQueue.hpp
            ClientEventHandler.cpp ClientProtocol.cpp GameGUI.cpp
            GameInitializer.cpp ProtocolEnumTranslator.cpp Update.h
            UpdateReceiver.cpp UpdateManager.cpp UpdateManager.h Update.cpp)

add_subdirectory(InputCommands)

target_link_libraries(client ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer texture graphics sound)