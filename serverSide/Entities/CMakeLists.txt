cmake_minimum_required(VERSION 3.16)

add_library(entities Entity.cpp Minichat.cpp Monster.cpp MonsterStats.cpp
        Player.cpp PlayerProxy.cpp PlayerStats.cpp MovementBackup.h)

add_subdirectory(Citizens)

target_link_libraries(entities PUBLIC citizens items server)