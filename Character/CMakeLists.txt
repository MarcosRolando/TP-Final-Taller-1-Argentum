cmake_minimum_required(VERSION 3.16)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(character NPC.cpp Player.cpp)

target_compile_options (character PRIVATE -std=c++11 -Wall -Werror -pedantic -pedantic-errors
        -O0 -ggdb -DDEBUG -fno-inline)

target_link_options(character PRIVATE -lm -pthread)

target_link_libraries(character ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer)