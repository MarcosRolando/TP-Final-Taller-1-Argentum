//
// Created by agustin on 22/6/20.
//

#ifndef ARGENTUM_ENTITYTESTS_H
#define ARGENTUM_ENTITYTESTS_H


#include "../Game/Game.h"

class EntityTests {
public:
    static bool testStoreItem();
    static bool testIsMonsterTarget();
    static bool testSpendGold();
    static bool testItemUse();
    static bool testPlayerNickname();
    static bool testLifeAndManaRecovery();
    static bool testUnequipGear();
    static bool testPlayerAttacksMonster();
    static bool testPlayerAttacksMonsterAndConsumesMana();
    static bool testPlayerAttacksNewbieAndViceversa();
    static bool testPlayerAttacksPlayerWithPastLevelDifferenceAndViceversa();
    static bool testPlayersAttackEachOther();
    static bool testMonsterAttacksPlayer();
    static bool testPlayerSellsItem();
    static bool testPlayerDepositsAnItem();

private:
    static bool _testUnequipWeapon(Game &game);
    static bool _testUnequipClothing(Game &game);
    static void _fillEmptyMap(Map &map, int iSize, int jSize, bool isCity);
};


#endif //ARGENTUM_ENTITYTESTS_H
