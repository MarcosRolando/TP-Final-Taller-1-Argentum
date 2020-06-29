//
// Created by marcos on 23/6/20.
//

#include "PlayerProxy.h"
#include "../Map/Coordinate.h"
#include "../Game/Game.h"
#include "../Game/Events/Attack.h"
#include "../Game/Events/Buy.h"
#include "../Game/Events/Sell.h"
#include "../Game/Events/Withdraw.h"
#include "../Game/Events/List.h"
#include "../Entities/Player.h"
#include "../Game/Events/Deposit.h"
#include "../Game/Events/Drop.h"
#include "../Game/Events/Unequip.h"
#include "../Game/Events/UseItem.h"
#include "../Game/Events/Move.h"

#define MAX_EVENTS_STORED 3

void PlayerProxy::attack(Coordinate target) {
    /*
    std::unique_ptr<Attack> event(new Attack(player, target));
    game.pushEvent(std::move(event));
    */
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Attack(player, target));
    }
}

void PlayerProxy::useItem(int itemPosition) {
    /*
    std::unique_ptr<UseItem> event(new UseItem(player, itemPosition));
    game.pushEvent(std::move(event));
    */
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new UseItem(player, itemPosition));
    }
}

void PlayerProxy::meditate() {
    player.meditate();
}

void PlayerProxy::move(GameType::Direction direction) {
    /*
    player.requestMove(direction);
    */
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Move(game, player, direction));
    }
}

void PlayerProxy::buyFrom(std::string &&itemName, Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Buy(player, itemName, npcPosition));
    }
}

void PlayerProxy::sellTo(std::string &&itemName, Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Sell(player, itemName, npcPosition));
    }
}

void PlayerProxy::withdrawFrom(std::string &&itemName, Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Withdraw(player, itemName, npcPosition));
    }
}

void PlayerProxy::listFrom(Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new List(player, npcPosition));
    }
}

void PlayerProxy::depositTo(std::string &&itemName, Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Deposit(player, itemName, npcPosition));
    }
}

void PlayerProxy::unequip() {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Unequip(player));
    }
}

void PlayerProxy::unequip(EquipmentPlace clothing) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Unequip(player, clothing));
    }
}

void PlayerProxy::dropItem(unsigned int itemPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Drop(player, itemPosition));
    }
}

const Player &PlayerProxy::getPlayer() const {
    return player;
}
