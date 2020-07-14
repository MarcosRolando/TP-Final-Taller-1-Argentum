cmake_minimum_required(VERSION 3.16)

add_library(updateEvents UpdateAttack.cpp UpdateCreateItem.cpp UpdateCreateNPC.cpp
            UpdateCreatePlayer.cpp UpdateDestroyItem.cpp UpdateEquip.cpp
            UpdateGUI.cpp UpdateMove.cpp UpdatePlayerDeath.cpp
            UpdatePlayerResurrect.cpp UpdateRemoveEntity.cpp UpdateTeleportEntity.cpp)

target_link_libraries(updateEvents clientMap)