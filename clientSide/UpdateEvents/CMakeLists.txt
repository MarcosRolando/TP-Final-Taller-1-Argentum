cmake_minimum_required(VERSION 3.10.2)

add_library(updateEvents UpdateAttack.cpp UpdateCreateItem.cpp UpdateCreateNPC.cpp
            UpdateCreatePlayer.cpp UpdateDestroyItem.cpp UpdateEquip.cpp
            UpdateGUI.cpp UpdateMove.cpp UpdatePlayerDeath.cpp
            UpdatePlayerResurrect.cpp UpdateRemoveEntity.cpp UpdateTeleportEntity.cpp UpdateLevelUp.cpp UpdateLevelUp.h)

target_link_libraries(updateEvents clientMap)
