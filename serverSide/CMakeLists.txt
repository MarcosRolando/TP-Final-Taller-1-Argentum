cmake_minimum_required(VERSION 3.16)

add_subdirectory(Config)
add_subdirectory(Entities)
add_subdirectory(Game)
add_subdirectory(Items)
add_subdirectory(Map)
add_subdirectory(Persistance)
add_subdirectory(Server)
add_subdirectory(Tests)

add_executable(argentumServer serverMain.cpp)

target_link_libraries(argentumServer server persistance serverMap items game
                        entities config libs)
