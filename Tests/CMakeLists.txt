cmake_minimum_required(VERSION 3.16)

add_executable(tests tests.cpp MapTests.cpp MapTests.h ItemTests.cpp
        ItemTests.h GameTests.cpp GameTests.h EntityTests.cpp EntityTests.h item_tests.cpp ../Items/Item.h ../Items/Attack/Weapon.cpp ../Items/Attack/Weapon.h
        ../Items/Miscellaneous/Gold.cpp ../Items/Miscellaneous/Gold.h ../Map/Tile.cpp ../Map/Tile.h ../Map/FloorType.h ../Entities/Entity.h
        ../Map/Coordinate.h ../Entities/Monster.cpp ../Entities/Monster.h ../Game/Game.cpp ../Game/Game.h ../Map/Map.cpp
        ../Map/Map.h ../Items/Inventory.cpp ../Items/Inventory.h ../Entities/Player.cpp ../Entities/Player.h
        ../Entities/Entity.cpp ../Items/Defense/Clothing.cpp ../Items/Defense/Clothing.h ../Items/Defense/Head.cpp
        ../Items/Defense/Head.h ../Items/Defense/Shield.cpp ../Items/Defense/Shield.h ../Items/Defense/Chest.cpp
        ../Items/Defense/Chest.h ../Items/Item.cpp ../Map/InverseCoordinateDistance.cpp ../Map/InverseCoordinateDistance.h
        ../Map/PointAndDistance.h ../Entities/PlayerStats.cpp ../Entities/PlayerStats.h ../Entities/Citizens/Banker.cpp ../Entities/Citizens/Banker.h
        ../Entities/Citizens/Storage.cpp ../Entities/Citizens/Storage.h ../Entities/Citizens/Trader.cpp ../Entities/Citizens/Trader.h
        ../Entities/Citizens/Priest.cpp ../Entities/Citizens/Priest.h ../Entities/Citizens/Shop.cpp ../Entities/Citizens/Shop.h
        ../Items/ItemsFactory.cpp ../Items/ItemsFactory.h ../Config/Configuration.cpp ../Config/ConfigFileReader.cpp
        ../Config/Calculator.cpp
        ../AttackResult.h
        ../TPException.cpp ../Entities/MoveDirection.h ../Items/Miscellaneous/ManaPotion.cpp
        ../Items/Miscellaneous/ManaPotion.h ../Items/Miscellaneous/HealthPotion.cpp
        ../Items/Miscellaneous/HealthPotion.h ../Items/Miscellaneous/Potion.cpp
        ../Items/Miscellaneous/Potion.h ../Entities/MonsterStats.cpp ../Entities/MonsterStats.h
        ../Config/GameEnums.h ../Game/Argentum.cpp ../Game/Argentum.h ../Game/MonstersFactory.cpp
        ../Game/MonstersFactory.h ../Game/ShouldMonsterBeRemoved.cpp ../Game/ShouldMonsterBeRemoved.h map_tests.cpp)

target_compile_options (tests PRIVATE -std=c++11 -Wall -Werror -pedantic -pedantic-errors
        -O3 -ggdb -DDEBUG -fno-inline -ljsoncpp)

target_link_options(tests PRIVATE -lm -pthread)

target_link_libraries(tests ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer jsoncpp ${Boost_LIBRARIES})