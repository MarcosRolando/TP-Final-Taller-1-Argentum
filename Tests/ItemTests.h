//
// Created by agustin on 22/6/20.
//

#ifndef ARGENTUM_ITEMTESTS_H
#define ARGENTUM_ITEMTESTS_H

class Configuration;

class ItemTests {
public:
    static bool testInitialValues();
    static bool testAreNonGoldItemsGold();
    static bool testIsGoldItemGold();
    static bool testCorrectItemsNames();
    static bool testCorrectGoldAmount();

private:
    static bool _testCorrectItemsNamesHelmets(Configuration& config);
    static bool _testCorrectItemsNamesWeapons(Configuration& config);
    static bool _testCorrectItemsNamesPotions(Configuration& config);
    static bool _testCorrectItemsNamesShields(Configuration& config);
    static bool _testCorrectItemsNamesClothing(Configuration& config);
};


#endif //ARGENTUM_ITEMTESTS_H
