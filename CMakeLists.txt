cmake_minimum_required(VERSION 3.16)
project(Argentum)

add_compile_options(-std=c++11 -Wall -Werror -pedantic
        -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -ljsoncpp)

add_link_options(-lm -pthread)

add_subdirectory(serverSide)
add_subdirectory(clientSide)
add_subdirectory(libs)

