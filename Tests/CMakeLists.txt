cmake_minimum_required(VERSION 3.16)

add_executable(tests tests.cpp MapTests.cpp MapTests.h ItemTests.cpp
        ItemTests.h GameTests.cpp GameTests.h EntityTests.cpp EntityTests.h item_tests.cpp
        ../Items/Item.cpp)

target_compile_options (tests PRIVATE -std=c++11 -Wall -Werror -pedantic -pedantic-errors
        -O3 -ggdb -DDEBUG -fno-inline -ljsoncpp)

target_link_options(tests PRIVATE -lm -pthread)

target_link_libraries(tests ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer jsoncpp ${Boost_LIBRARIES})