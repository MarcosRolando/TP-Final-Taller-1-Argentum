cmake_minimum_required(VERSION 3.10.2)

add_library(character NPC.cpp Player.cpp Entity.cpp)

target_link_libraries(character texture)
