//
// Created by agustin on 22/6/20.
//

#ifndef ARGENTUM_ITEMTESTS_H
#define ARGENTUM_ITEMTESTS_H

class ItemTests {
public:
    static bool testInitialValues();
    static bool testAreNonGoldItemsGold();
    static bool testIsGoldItemGold();
    static bool testCorrectItemsNames();
    static bool testCorrectGoldAmount();

private:
    static bool _testCorrectItemsNamesHelmets();
    static bool _testCorrectItemsNamesWeapons();
    static bool _testCorrectItemsNamesPotions();
    static bool _testCorrectItemsNamesShields();
    static bool _testCorrectItemsNamesClothing();
};


#endif //ARGENTUM_ITEMTESTS_H
