cmake_minimum_required(VERSION 3.16)

add_library(map Map.cpp Tile.cpp Structure.cpp Structure.h ItemDrop.cpp ItemDrop.h Coordinate.h)

target_link_libraries(map character)