cmake_minimum_required(VERSION 3.16)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(jsoncpp)
include_directories(${jsoncpp_INCLUDE_DIRS})

add_subdirectory(Texture)
add_subdirectory(Map)
add_subdirectory(Character)
add_subdirectory(Sound)
add_subdirectory(Screen)
add_subdirectory(Graphics)
add_subdirectory(Client)
add_subdirectory(UpdateEvents)

add_executable(argentumClient clientMain.cpp Spells/Spell.cpp)

target_compile_options (argentumClient PUBLIC -std=c++11 -Wall -Werror -pedantic
        -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -ljsoncpp)

target_link_options(argentumClient PUBLIC -lm -pthread)

target_link_libraries(argentumClient jsoncpp ${Boost_LIBRARIES} )

target_link_libraries(argentumClient ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer
                        texture map character sound graphics client screen updateEvents
                        inputCommands libs)
