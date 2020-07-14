cmake_minimum_required(VERSION 3.16)

add_library(clientMap Map.cpp Tile.cpp Structure.cpp Structure.h ItemDrop.cpp ItemDrop.h Coordinate.h)

target_link_libraries(clientMap character clientMiscellaneous)