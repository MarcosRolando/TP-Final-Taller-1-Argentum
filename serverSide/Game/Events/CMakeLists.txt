cmake_minimum_required(VERSION 3.10.2)

add_library(events Attack.cpp Buy.cpp Deposit.cpp Drop.cpp Event.cpp
            List.cpp Message.cpp Move.cpp Moved.cpp NotifyDeath.cpp PickUpItem.cpp
            RequestResurrect.cpp RestoreStats.cpp Sell.cpp Unequip.cpp
            UseItem.cpp Withdraw.cpp GetInventoryNames.cpp GetInventoryNames.h ModifyPlayerMovement.cpp ModifyPlayerMovement.h PlayerLeveledUp.cpp PlayerLeveledUp.h)
