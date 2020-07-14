cmake_minimum_required(VERSION 3.16)

add_library(game Game.cpp MonstersFactory.cpp ShouldMonsterBeRemoved.cpp
            ShouldPlayerBeRevived.cpp)

add_subdirectory(Events)

target_link_libraries(game PUBLIC events)