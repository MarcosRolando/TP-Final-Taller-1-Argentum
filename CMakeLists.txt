cmake_minimum_required(VERSION 3.16)
project(Argentum)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(jsoncpp)
include_directories(${jsoncpp_INCLUDE_DIRS})

add_executable(argentum main.cpp SDL/SDLException.cpp SDL/SDLException.h SDL/SoundRepository.cpp SDL/SoundRepository.h SDL/Texture.cpp SDL/Texture.h SDL/Font.cpp SDL/Font.h SDL/Window.cpp SDL/Window.h SDL/Renderer.cpp SDL/Renderer.h FileReader.cpp FileReader.h Configuration.cpp Configuration.h SDL/Sound.cpp SDL/Sound.h)

target_compile_options (argentum PRIVATE -std=c++11 -Wall -Werror -pedantic
        -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -ljsoncpp)

target_link_options(argentum PRIVATE -lm -pthread)

target_link_libraries(argentum ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer)
target_link_libraries(argentum jsoncpp ${Boost_LIBRARIES} )