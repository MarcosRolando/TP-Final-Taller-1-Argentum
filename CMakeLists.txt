cmake_minimum_required(VERSION 3.16)
project(Argentum)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(argentum main.cpp SDLException.cpp SDLException.h Sounds.cpp Sounds.h)

target_compile_options (argentum PRIVATE -std=c++11 -Wall -Werror -pedantic -pedantic-errors
                                                            -O0 -ggdb -DDEBUG -fno-inline)

target_link_options(argentum PRIVATE -lm -pthread)

target_link_libraries(argentum ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer)