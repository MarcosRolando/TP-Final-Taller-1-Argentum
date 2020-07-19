cmake_minimum_required(VERSION 3.10.2)

add_library(server ArgentumServer.cpp ArgentumServerSide.cpp ClientAccepter.cpp
        ClientHandler.cpp ClientsMonitor.cpp PlayerData.hpp PlayerManager.cpp
        ServerMonitor.cpp ServerProtocol.cpp)

target_link_libraries(server entities)
