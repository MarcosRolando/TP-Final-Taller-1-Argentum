cmake_minimum_required(VERSION 3.16)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(texture NPCTexture.cpp PlayerTexture.cpp Texture.cpp)

target_compile_options (texture PRIVATE -std=c++11 -Wall -Werror -pedantic -pedantic-errors
        -O0 -ggdb -DDEBUG -fno-inline)

target_link_options(texture PRIVATE -lm -pthread)

target_link_libraries(texture ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer)