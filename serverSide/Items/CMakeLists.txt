cmake_minimum_required(VERSION 3.16)

add_library(items Inventory.cpp Item.cpp ItemsFactory.cpp)

add_subdirectory(Attack)
add_subdirectory(Defense)
add_subdirectory(Miscellaneous)

target_link_libraries(items PUBLIC attack defense miscellaneous)