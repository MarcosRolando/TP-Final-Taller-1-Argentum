//
// Created by marcos on 22/6/20.
//

#include "catch.hpp"
#include "EntityTests.h"

TEST_CASE("Store Item In Player Inventory Test") {
    REQUIRE(EntityTests::testStoreItem());
}

TEST_CASE("Player Is Monster Target Test") {
    REQUIRE(EntityTests::testIsMonsterTarget());
}

TEST_CASE("Gold Management By Player Test") {
    REQUIRE(EntityTests::testSpendGold());
}

TEST_CASE("Item Management By Player Test") {
    REQUIRE(EntityTests::testItemUse());
}

TEST_CASE("Correct Player Nickname Test") {
    REQUIRE(EntityTests::testPlayerNickname());
}

TEST_CASE("Life And Mana Recovery By Player Test") {
    REQUIRE(EntityTests::testLifeAndManaRecovery());
}

TEST_CASE("Unequip Gear Test") {
    REQUIRE(EntityTests::testUnequipGear());
}

TEST_CASE("Player Attacks Monster And Damages It Test") {
    REQUIRE(EntityTests::testPlayerAttacksMonster());
}

TEST_CASE("Player Attacks Monster And Consumes Weapon Mana Test") {
    REQUIRE(EntityTests::testPlayerAttacksMonsterAndConsumesMana());
}

TEST_CASE("Player Attacks Newbie And Viceversa Test") {
    REQUIRE(EntityTests::testPlayerAttacksNewbieAndViceversa());
}

TEST_CASE("Player Attacks Player With Past Level Difference And Viceversa Test") {
    REQUIRE(EntityTests::testPlayerAttacksPlayerWithPastLevelDifferenceAndViceversa());
}

TEST_CASE("Players Attack Each Other Test") {
    REQUIRE(EntityTests::testPlayersAttackEachOther());
}

TEST_CASE("Monster Attacks Player Test") {
    REQUIRE(EntityTests::testMonsterAttacksPlayer());
}

TEST_CASE("Trader And Priest Buy Item From Player") {
    REQUIRE(EntityTests::testPlayerSellsItem());
}

TEST_CASE("Player Deposits And Withdraws An Item") {
    REQUIRE(EntityTests::testPlayerDepositsAnItem());
}


