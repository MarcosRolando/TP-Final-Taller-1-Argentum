cmake_minimum_required(VERSION 3.16)
project(Argentum)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(jsoncpp)
include_directories(${jsoncpp_INCLUDE_DIRS})

add_executable(argentum main.cpp Items/Item.h Items/Attack/Weapon.cpp Items/Attack/Weapon.h
        Items/Miscellaneous/Gold.cpp Items/Miscellaneous/Gold.h Map/Tile.cpp Map/Tile.h Map/FloorType.h Entities/Entity.h
        Map/Coordinate.h Entities/Monster.cpp Entities/Monster.h Game.cpp Game.h Map/Map.cpp
        Map/Map.h Items/Inventory.cpp Items/Inventory.h Entities/Player.cpp Entities/Player.h
        Entities/Entity.cpp Items/Defense/Clothing.cpp Items/Defense/Clothing.h Items/Defense/Head/Head.cpp
        Items/Defense/Head/Head.h Items/Defense/Shield/Shield.cpp Items/Defense/Shield/Shield.h Items/Defense/Chest/Chest.cpp
        Items/Defense/Chest/Chest.h Items/Item.cpp Map/InverseCoordinateDistance.cpp Map/InverseCoordinateDistance.h
        Map/PointAndDistance.h Entities/PlayerStats.cpp Entities/PlayerStats.h Entities/Citizens/Banker.cpp Entities/Citizens/Banker.h
        Entities/Citizens/Storage.cpp Entities/Citizens/Storage.h Entities/Citizens/Trader.cpp Entities/Citizens/Trader.h
        Entities/Citizens/Priest.cpp Entities/Citizens/Priest.h Entities/Citizens/Shop.cpp Entities/Citizens/Shop.h
        Items/ItemsFactory.cpp Items/ItemsFactory.h Config/Configuration.cpp Config/ConfigFileReader.cpp Items/Defense/Head/IronHelmet.cpp
        Items/Defense/Head/IronHelmet.h Items/Defense/Shield/TurtleShield.cpp Items/Defense/Shield/TurtleShield.h
        Items/Defense/Shield/IronShield.cpp Items/Defense/Shield/IronShield.h Items/Defense/Head/MagicHat.cpp
        Items/Defense/Head/MagicHat.h Items/Defense/Head/Hood.cpp Items/Defense/Head/Hood.h
        Items/Defense/Chest/BlueTunic.cpp Items/Defense/Chest/BlueTunic.h Items/Defense/Chest/PlateArmor.cpp
        Items/Defense/Chest/PlateArmor.h Items/Defense/Chest/LeatherArmor.cpp Items/Defense/Chest/LeatherArmor.h
        Config/Calculator.cpp Items/Attack/CompositeBow.h Items/Attack/CompositeBow.cpp Items/Attack/SimpleBow.cpp
        Items/Attack/SimpleBow.h Items/Attack/LinkedStaff.cpp Items/Attack/LinkedStaff.h Items/Attack/GnarledStaff.cpp
        Items/Attack/GnarledStaff.h Items/Attack/ElvenFlute.cpp Items/Attack/ElvenFlute.h Items/Attack/AshRod.cpp Items/Attack/AshRod.h
        Items/Attack/Warhammer.cpp Items/Attack/Warhammer.h Items/Attack/Axe.cpp Items/Attack/Axe.h Items/Attack/Longsword.cpp
        Items/Attack/Longsword.h Items/Attack/Fist.cpp Items/Attack/Fist.h AttackResult.h Items/Defense/Chest/CommonClothing.cpp
        Items/Defense/Chest/CommonClothing.h Items/Defense/Head/NoHelmet.cpp Items/Defense/Head/NoHelmet.h Items/Defense/Shield/NoShield.cpp
        Items/Defense/Shield/NoShield.h TPException.cpp Entities/MoveDirection.h Items/Miscellaneous/ManaPotion.cpp Items/Miscellaneous/ManaPotion.h Items/Miscellaneous/HealthPotion.cpp Items/Miscellaneous/HealthPotion.h Items/Miscellaneous/Potion.cpp Items/Miscellaneous/Potion.h Argentum.cpp Argentum.h)

target_compile_options (argentum PRIVATE -std=c++11 -Wall -Werror -pedantic -pedantic-errors
                        -O0 -ggdb -DDEBUG -fno-inline -ljsoncpp)

target_link_options(argentum PRIVATE -lm -pthread)

target_link_libraries(argentum ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer jsoncpp ${Boost_LIBRARIES})