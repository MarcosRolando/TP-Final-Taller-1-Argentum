cmake_minimum_required(VERSION 3.16)
project(Argentum)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(jsoncpp)
include_directories(${jsoncpp_INCLUDE_DIRS})

add_subdirectory(Tests)

add_executable(argentum main.cpp Items/Item.h Items/Attack/Weapon.cpp Items/Attack/Weapon.h
        Items/Miscellaneous/Gold.cpp Items/Miscellaneous/Gold.h Map/Tile.cpp Map/Tile.h Entities/Entity.h
        Map/Coordinate.h Entities/Monster.cpp Entities/Monster.h Game/Game.cpp Game/Game.h Map/Map.cpp
        Map/Map.h Items/Inventory.cpp Items/Inventory.h Entities/Player.cpp Entities/Player.h
        Entities/Entity.cpp Items/Defense/Clothing.cpp Items/Defense/Clothing.h Items/Defense/Head.cpp
        Items/Defense/Head.h Items/Defense/Shield.cpp Items/Defense/Shield.h Items/Defense/Chest.cpp
        Items/Defense/Chest.h Items/Item.cpp Map/InverseCoordinateDistance.cpp Map/InverseCoordinateDistance.h
        Map/PointAndDistance.h Entities/PlayerStats.cpp Entities/PlayerStats.h Entities/Citizens/Banker.cpp Entities/Citizens/Banker.h
        Entities/Citizens/Storage.cpp Entities/Citizens/Storage.h Entities/Citizens/Trader.cpp Entities/Citizens/Trader.h
        Entities/Citizens/Priest.cpp Entities/Citizens/Priest.h Entities/Citizens/Shop.cpp Entities/Citizens/Shop.h
        Items/ItemsFactory.cpp Items/ItemsFactory.h Config/Configuration.cpp Config/ConfigFileReader.cpp
        Config/Calculator.cpp
        AttackResult.h
        TPException.cpp Entities/MoveDirection.h Items/Miscellaneous/ManaPotion.cpp
        Items/Miscellaneous/ManaPotion.h Items/Miscellaneous/HealthPotion.cpp
        Items/Miscellaneous/HealthPotion.h Items/Miscellaneous/Potion.cpp
        Items/Miscellaneous/Potion.h Entities/MonsterStats.cpp Entities/MonsterStats.h
        Config/GameEnums.h Game/MonstersFactory.cpp
        Game/MonstersFactory.h Game/ShouldMonsterBeRemoved.cpp Game/ShouldMonsterBeRemoved.h
        Game/Events/Event.cpp Game/Events/Event.h Game/Events/Attack.cpp Game/Events/Attack.h
        Game/Events/Move.cpp Game/Events/Move.h Game/Events/List.cpp Game/Events/List.h
        Game/Events/Withdraw.cpp Game/Events/Withdraw.h Game/Events/Deposit.cpp Game/Events/Deposit.h
        Game/Events/Buy.cpp Game/Events/Buy.h Game/Events/Sell.cpp Game/Events/Sell.h
        Game/Events/Drop.cpp Game/Events/Drop.h Entities/Citizens/ProductData.h
        Entities/PlayerProxy.cpp Entities/PlayerProxy.cpp Entities/PlayerProxy.h
        Game/Events/UseItem.cpp Game/Events/UseItem.h Game/Events/Unequip.cpp Game/Events/Unequip.h
        Server/ServerProtocol.cpp Server/ServerProtocol.h
        Server/ClientHandler.cpp Server/ArgentumServer.cpp Server/ServerMonitor.cpp Server/ServerMonitor.cpp
        Server/Socket.cpp Server/Thread.cpp Server/ArgentumServerSide.cpp Server/ClientAccepter.cpp Server/ClientAccepter.h
        Config/MapFileReader.cpp)


target_compile_options (argentum PRIVATE -std=c++11 -Wall -Werror -pedantic -pedantic-errors
                        -O0 -ggdb -DDEBUG -fno-inline -ljsoncpp)

target_link_options(argentum PRIVATE -lm -pthread)

target_link_libraries(argentum ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer jsoncpp ${Boost_LIBRARIES})