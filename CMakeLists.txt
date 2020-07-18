cmake_minimum_required(VERSION 3.16)
project(Argentum)

add_compile_options(-std=c++11 -Wall -Werror -pedantic
        -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline)

add_link_options(-lm -pthread)

add_subdirectory(serverSide)
add_subdirectory(clientSide)
add_subdirectory(libs)

file(COPY clientSide/Assets DESTINATION ./)
file(COPY serverSide/Config/config.json serverSide/Config/map.json DESTINATION ./)

INSTALL(TARGETS argentumServer argentumClient DESTINATION /usr/bin)
INSTALL(DIRECTORY clientSide/Assets DESTINATION /var/Argentum)
INSTALL(FILES serverSide/Config/config.json serverSide/Config/map.json DESTINATION /etc/Argentum)