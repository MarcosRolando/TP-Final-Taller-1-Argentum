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

