cmake_minimum_required(VERSION 3.10.2)
project(Argentum)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -lm -pthread")

add_subdirectory(serverSide)
add_subdirectory(clientSide)
add_subdirectory(libs)


INSTALL(DIRECTORY clientSide/Assets DESTINATION /var/Argentum)
INSTALL(FILES serverSide/Config/config.json serverSide/Config/map.json DESTINATION /etc/Argentum)
