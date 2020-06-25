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
    static bool testAddedGoldToMap();
    static bool testAddedMultipleGoldsToMapWithList();
    static bool testAddedMultipleGoldsToMapWithoutList();
    static bool testAddedMultipleItemsListsToMap();
    static bool testGetTargetsOnEmptyMapReturnsEmptyList();
    static bool testGetTargetsOnMapWithPlayerReturnsListWithOneElement();
    static bool testGetTargetsOnMapWithDeadPlayerReturnsEmptyList();
    static bool testPositionWithPlayerIsOccupied();
    static bool testPositionWithMonsterIsOccupied();

    static bool testListOnEmptyTileReturnsEmptyList();
    static bool testListOnEmptyMapReturnsEmptyList();
    static bool testWithdrawOnEmptyTileGetsNoItem();
    static bool testWithdrawOnEmptyMapGetsNoItem();
    static bool testDepositExistantItemOnEmptyTileGetsNoItem();
    static bool testDepositExistantItemOnEmptyMapGetsNoItem();
    static bool testBuyItemFromEmptyTileGetsNoItem();
    static bool testBuyItemFromEmptyMapGetsNoItem();
};


#endif //ARGENTUM_MAPTESTS_H
