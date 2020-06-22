//
// Created by agustin on 22/6/20.
//

#ifndef ARGENTUM_MAPTESTS_H
#define ARGENTUM_MAPTESTS_H

class Map;

class MapTests {
private:
    static void _fillEmptyMap(Map& map, int iSize, int jSize, bool isCity = false);

public:
    static bool testAvailableMapHasAvailableTiles();
    static bool testCityMapHasCityTiles();
    static bool testMixedCityAndUnavailableTiles();
    static bool testAddedItemsToMap();
};


#endif //ARGENTUM_MAPTESTS_H
