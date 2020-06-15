cmake_minimum_required(VERSION 3.16)
project(Argentum)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(jsoncpp)
include_directories(${jsoncpp_INCLUDE_DIRS})

add_subdirectory(Texture)
add_subdirectory(Map)
add_subdirectory(Character)

add_executable(argentum main.cpp SDL/SDLException.cpp SDL/SDLException.h
SDL/Sound/SoundRepository.cpp SDL/Sound/SoundRepository.h SDL/Text/Font.cpp SDL/Text/Font.h
        ConfigFileReader.cpp ConfigFileReader.h Configuration.cpp
Configuration.h SDL/Sound/Sound.cpp SDL/Sound/Sound.h Calculator.cpp Calculator.h
Map/Tile.cpp Map/Tile.h Map/Map.cpp Map/Map.h Character/Player.cpp
Character/Player.h Timer.cpp Timer.h GameConstants.h Character/NPC.cpp
Character/NPC.h Direction.h Character/Entity.cpp Character/Entity.h
Screen/Window.cpp Screen/Window.h SDL/Text/Text.cpp SDL/Text/Text.h SDL/GUI/PlayerInfoGUI.cpp
        SDL/GUI/PlayerInfoGUI.h SDL/GUI/PlayerInventoryGUI.cpp SDL/GUI/PlayerInventoryGUI.h
        Spells/Spell.cpp Spells/Spell.h MapFileReader.cpp MapFileReader.h)


target_compile_options (argentum PUBLIC -std=c++11 -Wall -Werror -pedantic
        -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -ljsoncpp)

target_link_options(argentum PUBLIC -lm -pthread)


target_link_libraries(argentum jsoncpp ${Boost_LIBRARIES} )

target_link_libraries(argentum ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer
                        texture map character)
