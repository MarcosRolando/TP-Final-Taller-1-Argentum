cmake_minimum_required(VERSION 3.16)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(Texture)
add_subdirectory(Map)
add_subdirectory(Character)
add_subdirectory(Sound)
add_subdirectory(Screen)
add_subdirectory(Graphics)
add_subdirectory(Miscellaneous)
add_subdirectory(Client)
add_subdirectory(UpdateEvents)

add_executable(argentumClient clientMain.cpp)

target_link_libraries(argentumClient ${Boost_LIBRARIES})

target_link_libraries(argentumClient texture clientMap character sound graphics
            client screen updateEvents inputCommands libs clientMiscellaneous)
