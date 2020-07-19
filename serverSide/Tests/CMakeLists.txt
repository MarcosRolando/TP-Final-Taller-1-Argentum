cmake_minimum_required(VERSION 3.10.2)

add_executable(tests entity_tests.cpp tests.cpp MapTests.cpp ItemTests.cpp
                        EntityTests.cpp item_tests.cpp map_tests.cpp)

target_compile_options (tests PRIVATE -std=c++11 -Wall -Werror -pedantic -pedantic-errors
        -O0 -ggdb -DDEBUG -fno-inline)


target_link_libraries(tests PRIVATE persistance serverMap items entities game server
                          config libs)
