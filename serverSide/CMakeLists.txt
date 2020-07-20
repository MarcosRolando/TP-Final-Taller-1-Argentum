cmake_minimum_required(VERSION 3.10.2)

OPTION(ENABLE_TESTS "Compile the tests" OFF)

add_definitions(-DENABLE_TESTS)

add_subdirectory(Config)
add_subdirectory(Entities)
add_subdirectory(Game)
add_subdirectory(Items)
add_subdirectory(Map)
add_subdirectory(Persistance)
add_subdirectory(Server)
if (ENABLE_TESTS)
    add_subdirectory(Tests)
endif ()
add_executable(argentumServer serverMain.cpp NonModifiableConstants.h)

target_compile_options(argentumServer PRIVATE)

target_link_libraries(argentumServer ${Boost_LIBRARIES} server persistance serverMap items game entities config libs)

INSTALL(TARGETS argentumServer DESTINATION /usr/bin)
INSTALL(TARGETS argentumServer DESTINATION /bin)
