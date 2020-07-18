cmake_minimum_required(VERSION 3.16)

find_package(jsoncpp)
include_directories(${jsoncpp_INCLUDE_DIRS})

add_library(server ArgentumServer.cpp ArgentumServerSide.cpp ClientAccepter.cpp
            ClientHandler.cpp ClientsMonitor.cpp PlayerData.hpp PlayerManager.cpp
            ServerMonitor.cpp ServerProtocol.cpp)

target_link_libraries(server jsoncpp ${Boost_LIBRARIES} entities)